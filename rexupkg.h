/* ****************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2023 erysdren
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * ************************************************************************* */

/* *************************************
 *
 * project: librex
 *
 * file: rexupkg.h
 *
 * authors: erysdren
 *
 * last modified: january 16 2023
 *
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_UPKG_H__
#define __LIBREX_UPKG_H__

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

/* *************************************
 *
 * the headers
 *
 * ********************************** */

/* rex */
#include "rexstd.h"
#include "rextypes.h"
#include "rexmem.h"

/* *************************************
 *
 * the types
 *
 * ********************************** */

/* upkg generation */
typedef struct upkg_generation_t
{
	int32 num_exports;
	int32 num_names;
} upkg_generation_t;

/* upkg name */
typedef struct upkg_name_t
{
	uint8 len_name;
	char *name;
	uint32 flags;
} upkg_name_t;

/* upkg export */
typedef struct upkg_export_t
{
	int32 class_index;		/* compact index */
	int32 super_index;		/* compact index */
	int32 package_index;
	int32 object_name;		/* compact index */
	uint32 object_flags;
	int32 len_serial;		/* compact index */
	int32 ofs_serial;		/* compact index */
} upkg_export_t;

/* upkg import */
typedef struct upkg_import_t
{
	int32 class_package;	/* compact index */
	int32 class_name;		/* compact index */
	int32 package_index;
	int32 object_name;		/* compact index */
} upkg_import_t;

/* upkg */
typedef struct upkg_t
{
	uint32 tag;
	uint16 format_version;
	uint16 licensee_version;
	uint32 package_flags;
	int32 num_names;
	int32 ofs_names;
	int32 num_exports;
	int32 ofs_exports;
	int32 num_imports;
	int32 ofs_imports;
	uint32 guid[4];
	int32 num_generations;
	upkg_generation_t *generations;
	upkg_name_t *names;
	upkg_export_t *exports;
	upkg_import_t *imports;
	FILE *handle;
} upkg_t;

/* *************************************
 *
 * the forward declarations
 *
 * ********************************** */

/* opening and closing upackages */
static upkg_t *upkg_open(const char *filename);
static void upkg_close(upkg_t *upkg);

/* utility functions */
static int32 upkg_read_compact_index(FILE *stream);
static void upkg_print_members(upkg_t *upkg, FILE *stream);

/* *************************************
 *
 * the functions
 *
 * ********************************** */

/*
 * opening and closing upackages
 */

/* read upackage file and return a upackage struct */
static upkg_t *upkg_open(const char *filename)
{
	/* variables */
	int i;
	upkg_t *upkg;

	/* allocate struct */
	upkg = (upkg_t *)LIBREX_CALLOC(1, sizeof(upkg_t));

	/* alloc failed */
	if (upkg == NULL)
	{
		upkg_close(upkg);
		return NULL;
	}

	/* open file handle */
	upkg->handle = fopen(filename, "rb");
	if (upkg->handle == NULL)
	{
		upkg_close(upkg);
		return NULL;
	}

	/* read in header */
	fread(upkg, offsetof(upkg_t, generations), 1, upkg->handle);

	/* check if tag is correct */
	if (upkg->tag != 2653586369)
	{
		upkg_close(upkg);
		return NULL;
	}

	/* allocate generations */
	upkg->generations = (upkg_generation_t *)LIBREX_CALLOC(upkg->num_generations, sizeof(upkg_generation_t));

	/* read in generations */
	fread(upkg->generations, sizeof(upkg_generation_t),
			upkg->num_generations, upkg->handle);

	/* allocate names */
	upkg->names = (upkg_name_t *)LIBREX_CALLOC(upkg->num_names, sizeof(upkg_name_t));

	/* read in names */
	fseek(upkg->handle, upkg->ofs_names, SEEK_SET);
	for (i = 0; i < upkg->num_names; i++)
	{
		fread(&upkg->names[i].len_name, sizeof(uint8), 1, upkg->handle);
		upkg->names[i].name = (char *)LIBREX_CALLOC(upkg->names[i].len_name, sizeof(char));
		fread(upkg->names[i].name, sizeof(char), upkg->names[i].len_name, upkg->handle);
		fread(&upkg->names[i].flags, sizeof(uint32), 1, upkg->handle);
	}

	/* allocate imports */
	upkg->imports = (upkg_import_t *)LIBREX_CALLOC(upkg->num_imports, sizeof(upkg_import_t));

	/* read in imports */
	fseek(upkg->handle, upkg->ofs_imports, SEEK_SET);
	for (i = 0; i < upkg->num_imports; i++)
	{
		upkg->imports[i].class_package = upkg_read_compact_index(upkg->handle);
		upkg->imports[i].class_name = upkg_read_compact_index(upkg->handle);
		fread(&upkg->imports[i].package_index, sizeof(int32), 1, upkg->handle);
		upkg->imports[i].object_name = upkg_read_compact_index(upkg->handle);
	}

	/* allocate exports */
	upkg->exports = (upkg_export_t *)LIBREX_CALLOC(upkg->num_exports, sizeof(upkg_export_t));

	/* read in exports */
	fseek(upkg->handle, upkg->ofs_exports, SEEK_SET);
	for (i = 0; i < upkg->num_exports; i++)
	{
		upkg->exports[i].class_index = upkg_read_compact_index(upkg->handle);
		upkg->exports[i].super_index = upkg_read_compact_index(upkg->handle);
		fread(&upkg->exports[i].package_index, sizeof(int32), 1, upkg->handle);
		upkg->exports[i].object_name = upkg_read_compact_index(upkg->handle);
		fread(&upkg->exports[i].object_flags, sizeof(uint32), 1, upkg->handle);
		upkg->exports[i].len_serial = upkg_read_compact_index(upkg->handle);

		if (upkg->exports[i].len_serial > 0)
			upkg->exports[i].ofs_serial = upkg_read_compact_index(upkg->handle);
	}

	return upkg;
}

/* free all memory associated with a upackage struct */
static void upkg_close(upkg_t *upkg)
{
	int i;

	if (upkg)
	{
		if (upkg->generations)
			LIBREX_FREE(upkg->generations);

		if (upkg->names)
		{
			for (i = 0; i < upkg->num_names; i++)
			{
				if (upkg->names[i].name)
					LIBREX_FREE(upkg->names[i].name);
			}

			LIBREX_FREE(upkg->names);
		}

		if (upkg->exports)
			LIBREX_FREE(upkg->exports);

		if (upkg->imports)
			LIBREX_FREE(upkg->imports);

		if (upkg->handle)
			fclose(upkg->handle);

		LIBREX_FREE(upkg);
	}
}

/*
 * utility functions
 */

/* read unreal engine compact index */
static int32 upkg_read_compact_index(FILE *stream)
{
	int32 ret;
	uint8 x;
	int sign;
	int i;

	sign = 1;
	ret = 0;

	if (stream == NULL) return ret;

	for (i = 0; i < 5; i++)
	{
		fread(&x, sizeof(uint8), 1, stream);

		if (i == 0)
		{
			/*
			 * first byte
			 */

			/* bit: X0000000 */
			if ((x & 0x80) > 0)
				sign = -1;

			/* bits: 00XXXXXX */
			ret |= (x & 0x3F);

			/* bit: 0X000000 */
			if ((x & 0x40) == 0)
				break;
		}
		else if (i == 4)
		{
			/*
			 * last byte
			 */

			/*
			 * bits: 000XXXXX -- the 0 bits are ignored
			 * (hits the 32 bit boundary)
			 */
			ret |= (x & 0x1F) << (6 + (3 * 7));
		}
		else
		{
			/*
			 * middle byte
			 */

			/* bits: 0XXXXXXX */
			ret |= (x & 0x7F) << (6 + ((i - 1) * 7));

			/* bit: X0000000 */
			if ((x & 0x80) == 0)
				break;
		}
	}

	/* multiply by the sign */
	ret *= sign;

	/* return the unpacked integer */
	return ret;
}

/* print all members of a upackage */
static void upkg_print_members(upkg_t *upkg, FILE *stream)
{
	/* variables */
	int i;

	/* sanity checks */
	assert(upkg && stream);

	fprintf(stream, "\n");
	fprintf(stream, "|______upkg______|\n");
	fprintf(stream, "\n");

	/* print header */
	fprintf(stream, "\n");
	fprintf(stream, "|___header___|\n");
	fprintf(stream, "\n\n");

	fprintf(stream, "tag: %u\n", upkg->tag);
	fprintf(stream, "format_version: %u\n", upkg->format_version);
	fprintf(stream, "licensee_version: %u\n", upkg->licensee_version);
	fprintf(stream, "package_flags: %u\n", upkg->package_flags);
	fprintf(stream, "num_names: %d\n", upkg->num_names);
	fprintf(stream, "ofs_names: %d\n", upkg->ofs_names);
	fprintf(stream, "num_exports: %d\n", upkg->num_exports);
	fprintf(stream, "ofs_exports: %d\n", upkg->ofs_exports);
	fprintf(stream, "num_imports: %d\n", upkg->num_imports);
	fprintf(stream, "ofs_imports: %d\n", upkg->ofs_imports);
	fprintf(stream, "guid[0]: %u\n", upkg->guid[0]);
	fprintf(stream, "guid[1]: %u\n", upkg->guid[1]);
	fprintf(stream, "guid[2]: %u\n", upkg->guid[2]);
	fprintf(stream, "guid[3]: %u\n", upkg->guid[3]);
	fprintf(stream, "num_generations: %d\n", upkg->num_generations);

	/* print generations */
	fprintf(stream, "\n\n");
	fprintf(stream, "|___generations table___|\n");
	fprintf(stream, "\n\n");

	for (i = 0; i < upkg->num_generations; i++)
	{
		fprintf(stream, "generations[%d]\n", i);

		fprintf(stream, "\tnum_exports: %d\n",
			upkg->generations[i].num_exports);

		fprintf(stream, "\tnum_names: %d\n",
			upkg->generations[i].num_names);

		fprintf(stream, "\n");
	}

	/* print names */
	fprintf(stream, "\n");
	fprintf(stream, "|___name table___|\n");
	fprintf(stream, "\n\n");

	for (i = 0; i < upkg->num_names; i++)
	{
		fprintf(stream, "names[%d]: %s\n", i, upkg->names[i].name);
	}

	/* print imports */
	fprintf(stream, "\n\n");
	fprintf(stream, "|___import table___|\n");
	fprintf(stream, "\n\n");

	for (i = 0; i < upkg->num_imports; i++)
	{
		fprintf(stream, "imports[%d]\n", i);

		fprintf(stream, "\tclass_package: %d\n",
			upkg->imports[i].class_package);

		fprintf(stream, "\tclass_name: %d\n",
			upkg->imports[i].class_name);

		fprintf(stream, "\tpackage_index: %d\n",
			upkg->imports[i].package_index);

		fprintf(stream, "\tobject_name: [%d]: %s\n",
			upkg->imports[i].object_name,
			upkg->names[upkg->imports[i].object_name].name);

		fprintf(stream, "\n");
	}

	/* print exports */
	fprintf(stream, "\n");
	fprintf(stream, "|___export table___|\n");
	fprintf(stream, "\n\n");

	for (i = 0; i < upkg->num_exports; i++)
	{
		fprintf(stream, "exports[%d]\n", i);

		fprintf(stream, "\tclass_index: %d\n",
			upkg->exports[i].class_index);

		fprintf(stream, "\tsuper_index: %d\n",
			upkg->exports[i].super_index);

		fprintf(stream, "\tpackage_index: %d\n",
			upkg->exports[i].package_index);

		fprintf(stream, "\tobject_name: [%d] %s\n",
			upkg->exports[i].object_name,
			upkg->names[upkg->exports[i].object_name].name);

		fprintf(stream, "\tobject_flags: %u\n", upkg->exports[i].object_flags);
		fprintf(stream, "\tlen_serial: %d\n", upkg->exports[i].len_serial);
		fprintf(stream, "\tofs_serial: %u\n", upkg->exports[i].ofs_serial);
		fprintf(stream, "\n");
	}
}

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_UPKG_H__ */
