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
 * project: libupkg
 *
 * file: upkg.h
 *
 * authors: erysdren
 *
 * last modified: january 11 2023
 *
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBUPKG_H__
#define __LIBUPKG_H__

/* malloc */
#ifndef LIBUPKG_MALLOC
#define LIBUPKG_MALLOC(s) malloc(s)
#endif

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

/* *************************************
 *
 * the headers
 *
 * ********************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* *************************************
 *
 * the types
 *
 * ********************************** */

/* libupkg return values */
typedef enum upkg_ret
{
	UPKG_SUCCESS = 0,
	UPKG_COULDNT_OPEN_FILE = -1,
	UPKG_UNSUPPORTED_TAG = -2,
	UPKG_UNSUPPORTED_VERSION = -3,
	UPKG_INDEX_OUT_OF_RANGE = -4,
	UPKG_INVALID_FILE_HANDLE = -5,
	UPKG_TOO_MANY_BYTES_REQUESTED = -6,
	UPKG_ALLOC_FAILED = -7,
	UPKG_FOPEN_FAILED = -8,
	UPKG_FSEEK_FAILED = -9,
	UPKG_FREAD_FAILED = -10,
	UPKG_FTELL_FAILED = -11
} upkg_ret;

/* ugeneration */
typedef struct ugeneration_t
{
	int32_t num_exports;
	int32_t num_names;
} ugeneration_t;

/* uname */
typedef struct uname_t
{
	uint8_t len_name;
	char *name;
	uint32_t flags;
} uname_t;

/* uexport */
typedef struct uexport_t
{
	int32_t class_index;	/* compact index */
	int32_t super_index;	/* compact index */
	int32_t package_index;
	int32_t object_name;	/* compact index */
	uint32_t object_flags;
	int32_t len_serial;		/* compact index */
	int32_t ofs_serial;		/* compact index */
	long pos;
} uexport_t;

/* uimport */
typedef struct uimport_t
{
	int32_t class_package;	/* compact index */
	int32_t class_name;		/* compact index */
	int32_t package_index;
	int32_t object_name;	/* compact index */
} uimport_t;

/* upackage */
typedef struct upkg_t
{
	uint32_t tag;
	uint16_t format_version;
	uint16_t licensee_version;
	uint32_t package_flags;
	int32_t num_names;
	int32_t ofs_names;
	int32_t num_exports;
	int32_t ofs_exports;
	int32_t num_imports;
	int32_t ofs_imports;
	uint32_t guid[4];
	int32_t num_generations;
	ugeneration_t *generations;
	uname_t *names;
	uexport_t *exports;
	uimport_t *imports;
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
static int32_t upkg_read_compact_index(FILE *stream);
static void upkg_print_members(upkg_t *upkg, FILE *stream);

/* reading data from objects contained in a package */
static size_t upkg_fread(void *d, size_t s, size_t n, upkg_t *upkg, int i);
static int upkg_fseek(long offset, int whence, upkg_t *upkg, int i);
static long upkg_ftell(upkg_t *upkg, int i);
static long upkg_fsize(upkg_t *upkg, int i);

/* *************************************
 *
 * the functions
 *
 * ********************************** */

/*
 * opening and closing upackages
 */

/* failed attempt at mempool stuff */
static upkg_t *upkg_open_new(const char *filename)
{
	/* variables */
	int i;
	uint8_t u8;
	upkg_t *upkg;
	upkg_t utemp;
	FILE *ftemp;
	size_t alloc_size;
	size_t ptr_ofs;
	char buf[256];

	/* open temporary file handle */
	ftemp = fopen(filename, "rb");
	if (!ftemp) return NULL;

	/* read in temporary struct so we know how much memory to allocate */
	memset(&utemp, '\0', sizeof(upkg_t));
	fread(&utemp, offsetof(upkg_t, generations), 1, ftemp);

	/* start adding up the memory we need to alloc */
	alloc_size = sizeof(upkg_t);
	alloc_size += sizeof(ugeneration_t) * utemp.num_generations;
	alloc_size += sizeof(uname_t) * utemp.num_names;
	alloc_size += sizeof(uexport_t) * utemp.num_exports;
	alloc_size += sizeof(uimport_t) * utemp.num_imports;

	/* ...read through all names so we know how much memory to alloc... */
	fseek(ftemp, utemp.ofs_names, SEEK_SET);
	for (i = 0; i < utemp.num_names; i++)
	{
		fread(&u8, sizeof(uint8_t), 1, ftemp);
		alloc_size += u8;
		fseek(ftemp, u8 + sizeof(uint32_t), SEEK_CUR);
	}

	/* align our alloc_size to 4 bytes */
	alloc_size += alloc_size % 4;

	/* finally alloc our struct! */
	upkg = (upkg_t *)LIBUPKG_MALLOC(alloc_size);
	memset(upkg, '\0', alloc_size);

	/* memcpy our data instead of reading it again */
	memcpy(upkg, &utemp, offsetof(upkg_t, generations));

	/* copy handle */
	upkg->handle = ftemp;

	/* set the pointers */
	ptr_ofs = sizeof(upkg_t);
	upkg->generations = (ugeneration_t *)(upkg + ptr_ofs);

	ptr_ofs += sizeof(ugeneration_t) * upkg->num_generations;
	upkg->names = (uname_t *)(upkg + ptr_ofs);

	ptr_ofs += sizeof(uname_t) * upkg->num_names;
	upkg->exports = (uexport_t *)(upkg + ptr_ofs);

	ptr_ofs += sizeof(uexport_t) * upkg->num_exports;
	upkg->imports = (uimport_t *)(upkg + ptr_ofs);

	ptr_ofs += sizeof(uimport_t) * upkg->num_imports;

	/* read in generations */
	fseek(upkg->handle, offsetof(upkg_t, generations), SEEK_SET);
	fread(upkg->generations, sizeof(ugeneration_t),
			upkg->num_generations, upkg->handle);

	/* read in exports */
	fseek(upkg->handle, upkg->ofs_exports, SEEK_SET);
	for (i = 0; i < upkg->num_exports; i++)
	{
		upkg->exports[i].class_index = upkg_read_compact_index(upkg->handle);
		upkg->exports[i].super_index = upkg_read_compact_index(upkg->handle);
		fread(&upkg->exports[i].package_index, sizeof(int32_t), 1, upkg->handle);
		upkg->exports[i].object_name = upkg_read_compact_index(upkg->handle);
		fread(&upkg->exports[i].object_flags, sizeof(uint32_t), 1, upkg->handle);
		upkg->exports[i].len_serial = upkg_read_compact_index(upkg->handle);

		if (upkg->exports[i].len_serial > 0)
			upkg->exports[i].ofs_serial = upkg_read_compact_index(upkg->handle);
	}

	/* read in imports */
	fseek(upkg->handle, upkg->ofs_imports, SEEK_SET);
	for (i = 0; i < upkg->num_imports; i++)
	{
		upkg->imports[i].class_package = upkg_read_compact_index(upkg->handle);
		upkg->imports[i].class_name = upkg_read_compact_index(upkg->handle);
		fread(&upkg->imports[i].package_index, sizeof(int32_t), 1, upkg->handle);
		upkg->imports[i].object_name = upkg_read_compact_index(upkg->handle);
	}

	/* REMOVEME: temp stuff */
	printf("num_names: %d\n", upkg->num_names);
	printf("num_generations: %d\n", upkg->num_generations);
	printf("num_exports: %d\n", upkg->num_exports);
	printf("num_imports: %d\n", upkg->num_imports);
	printf("alloc_size: %lu\n", alloc_size);

	return upkg;
}

/* read upackage file and return a upackage struct */
static upkg_t *upkg_open(const char *filename)
{
	/* variables */
	int i;
	upkg_t *upkg;

	/* allocate struct */
	upkg = (upkg_t *)calloc(1, sizeof(upkg_t));

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
	upkg->generations = (ugeneration_t *)calloc(upkg->num_generations, sizeof(ugeneration_t));

	/* read in generations */
	fread(upkg->generations, sizeof(ugeneration_t), upkg->num_generations, upkg->handle);

	/* allocate names */
	upkg->names = (uname_t *)calloc(upkg->num_names, sizeof(uname_t));

	/* read in names */
	fseek(upkg->handle, upkg->ofs_names, SEEK_SET);
	for (i = 0; i < upkg->num_names; i++)
	{
		fread(&upkg->names[i].len_name, sizeof(uint8_t), 1, upkg->handle);
		upkg->names[i].name = (char *)calloc(upkg->names[i].len_name, sizeof(char));
		fread(upkg->names[i].name, sizeof(char), upkg->names[i].len_name, upkg->handle);
		fread(&upkg->names[i].flags, sizeof(uint32_t), 1, upkg->handle);
	}

	/* allocate imports */
	upkg->imports = (uimport_t *)calloc(upkg->num_imports, sizeof(uimport_t));

	/* read in imports */
	fseek(upkg->handle, upkg->ofs_imports, SEEK_SET);
	for (i = 0; i < upkg->num_imports; i++)
	{
		upkg->imports[i].class_package = upkg_read_compact_index(upkg->handle);
		upkg->imports[i].class_name = upkg_read_compact_index(upkg->handle);
		fread(&upkg->imports[i].package_index, sizeof(int32_t), 1, upkg->handle);
		upkg->imports[i].object_name = upkg_read_compact_index(upkg->handle);
	}

	/* allocate exports */
	upkg->exports = (uexport_t *)calloc(upkg->num_exports, sizeof(uexport_t));

	/* read in exports */
	fseek(upkg->handle, upkg->ofs_exports, SEEK_SET);
	for (i = 0; i < upkg->num_exports; i++)
	{
		upkg->exports[i].class_index = upkg_read_compact_index(upkg->handle);
		upkg->exports[i].super_index = upkg_read_compact_index(upkg->handle);
		fread(&upkg->exports[i].package_index, sizeof(int32_t), 1, upkg->handle);
		upkg->exports[i].object_name = upkg_read_compact_index(upkg->handle);
		fread(&upkg->exports[i].object_flags, sizeof(uint32_t), 1, upkg->handle);
		upkg->exports[i].len_serial = upkg_read_compact_index(upkg->handle);

		if (upkg->exports[i].len_serial > 0)
			upkg->exports[i].ofs_serial = upkg_read_compact_index(upkg->handle);

		upkg->exports[i].pos = 0;
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
			free(upkg->generations);

		if (upkg->names)
		{
			for (i = 0; i < upkg->num_names; i++)
			{
				if (upkg->names[i].name)
					free(upkg->names[i].name);
			}

			free(upkg->names);
		}

		if (upkg->exports)
			free(upkg->exports);

		if (upkg->imports)
			free(upkg->imports);

		if (upkg->handle)
			fclose(upkg->handle);

		free(upkg);
	}
}

/*
 * utility functions
 */

/* read unreal engine compact index */
static int32_t upkg_read_compact_index(FILE *stream)
{
	int32_t ret;
	uint8_t x;
	int sign;
	int i;

	sign = 1;
	ret = 0;

	if (stream == NULL) return ret;

	for (i = 0; i < 5; i++)
	{
		fread(&x, sizeof(uint8_t), 1, stream);

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
	int i;

	if (!upkg || !stream) return;

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

/*
 * reading data from objects contained in a package
 */

/* works like fread, except relative to the export object specified with i */
static size_t upkg_fread(void *d, size_t s, size_t n, upkg_t *upkg, int i)
{
	int pos;

	/* error checking */
	if (!upkg->handle)
		return UPKG_INVALID_FILE_HANDLE;
	if (i >= upkg->num_exports)
		return UPKG_INDEX_OUT_OF_RANGE;
	if ((s * n) > upkg->exports[i].len_serial)
		return UPKG_TOO_MANY_BYTES_REQUESTED;

	/* seek to position in file handle */
	pos = upkg->exports[i].ofs_serial + upkg->exports[i].pos;
	fseek(upkg->handle, pos, SEEK_SET);

	/* do an fread */
	return fread(d, s, n, upkg->handle);
}

/* works like fseek, except relative to the export object specified with i */
static int upkg_fseek(long offset, int whence, upkg_t *upkg, int i)
{
	/* error checking */
	if (!upkg->handle)
		return UPKG_INVALID_FILE_HANDLE;
	if (i >= upkg->num_exports)
		return UPKG_INDEX_OUT_OF_RANGE;

	switch (whence)
	{
		case SEEK_SET:
			upkg->exports[i].pos = offset;
			break;

		case SEEK_CUR:
			upkg->exports[i].pos += offset;
			break;

		case SEEK_END:
			upkg->exports[i].pos = upkg->exports[i].len_serial + offset;
			break;

		default:
			break;
	}

	/* error checking */
	if (upkg->exports[i].pos > upkg->exports[i].len_serial)
		upkg->exports[i].pos = upkg->exports[i].len_serial;

	if (upkg->exports[i].pos < 0)
		upkg->exports[i].pos = 0;

	return 0;
}

/* works like ftell, except relative to the export object specified with i */
static long upkg_ftell(upkg_t *upkg, int i)
{
	/* error checking */
	if (!upkg->handle)
		return UPKG_INVALID_FILE_HANDLE;
	if (i >= upkg->num_exports)
		return UPKG_INDEX_OUT_OF_RANGE;

	return upkg->exports[i].pos;
}

/* returns the size (in bytes) of the export object specified with i */
static long upkg_fsize(upkg_t *upkg, int i)
{
	/* error checking */
	if (!upkg->handle)
		return UPKG_INVALID_FILE_HANDLE;
	if (i >= upkg->num_exports)
		return UPKG_INDEX_OUT_OF_RANGE;

	return upkg->exports[i].len_serial;
}

#ifdef __cplusplus
}
#endif

#endif /* __LIBUPKG_H__ */
