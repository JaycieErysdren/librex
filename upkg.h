//==============================================================================
//
// MIT License
//
// Copyright (c) 2023 erysdren
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//==============================================================================

//=========================================
//
// project: libupkg
//
// file: upkg.h
//
// authors: erysdren
//
// last modified: january 9 2023
//
//=========================================

#pragma once
#ifndef __LIBUPKG_H__
#define __LIBUPKG_H__

#ifdef __cplusplus
extern "C" {
#endif

//=========================================
//
// the headers
//
//=========================================

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

//=========================================
//
// the types
//
//=========================================

// ugeneration
typedef struct
{

	// persisent
	int32_t num_exports;
	int32_t num_names;

} ugeneration_t;

// uname
typedef struct
{

	// persisent
	uint8_t len_name;
	char *name;
	uint32_t flags;

} uname_t;

// uexport
typedef struct
{

	// persisent
	int32_t class_index;	// compact index
	int32_t super_index;	// compact index
	int32_t package_index;
	int32_t object_name;	// compact index
	uint32_t object_flags;
	int32_t len_serial;		// compact index
	int32_t ofs_serial;		// compact index

	// libupkg
	long pos;

} uexport_t;

// uimport
typedef struct
{

	// persisent
	int32_t class_package;	// compact index
	int32_t class_name;		// compact index
	int32_t package_index;
	int32_t object_name;	// compact index

} uimport_t;

// upackage
typedef struct
{

	// persistent
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

	// libupkg
	FILE *fhandle;

} upackage_t;

//=========================================
//
// the forward declarations
//
//=========================================

// opening and closing upackages
static upackage_t *upkg_open(const char *filename);
static void upkg_close(upackage_t *upkg);

// utility functions
static int32_t upkg_read_compact_index(FILE *stream);
static void upkg_print_members(upackage_t *upkg, FILE *stream);

// reading data from objects contained in a package
static size_t upkg_fread(void *dest, size_t size, size_t n, upackage_t *upkg, int export_index);
static int upkg_fseek(long offset, int whence, upackage_t *upkg, int export_index);
static long upkg_ftell(upackage_t *upkg, int export_index);

//=========================================
//
// the functions
//
//=========================================

//
// opening and closing upackages
//

// read upackage file and return a upackage struct
static upackage_t *upkg_open(const char *filename)
{
	int i;

	// allocate struct
	upackage_t *upkg = (upackage_t *)calloc(1, sizeof(upackage_t));

	// open file handle
	upkg->fhandle = fopen(filename, "rb");
	if (upkg->fhandle == NULL)
	{
		upkg_close(upkg);
		return NULL;
	}

	// read in header
	fread(upkg, offsetof(upackage_t, generations), 1, upkg->fhandle);

	// check if tag is correct
	if (upkg->tag != 2653586369) return NULL;

	// allocate generations
	upkg->generations = (ugeneration_t *)calloc(upkg->num_generations, sizeof(ugeneration_t));

	// read in generations
	fread(upkg->generations, sizeof(ugeneration_t), upkg->num_generations, upkg->fhandle);

	// allocate names
	upkg->names = (uname_t *)calloc(upkg->num_names, sizeof(uname_t));

	// read in names
	fseek(upkg->fhandle, upkg->ofs_names, SEEK_SET);
	for (i = 0; i < upkg->num_names; i++)
	{
		fread(&upkg->names[i].len_name, sizeof(uint8_t), 1, upkg->fhandle);
		upkg->names[i].name = (char *)calloc(upkg->names[i].len_name, sizeof(char));
		fread(upkg->names[i].name, sizeof(char), upkg->names[i].len_name, upkg->fhandle);
		fread(&upkg->names[i].flags, sizeof(uint32_t), 1, upkg->fhandle);
	}

	// allocate imports
	upkg->imports = (uimport_t *)calloc(upkg->num_imports, sizeof(uimport_t));

	// read in imports
	fseek(upkg->fhandle, upkg->ofs_imports, SEEK_SET);
	for (i = 0; i < upkg->num_imports; i++)
	{
		upkg->imports[i].class_package = upkg_read_compact_index(upkg->fhandle);
		upkg->imports[i].class_name = upkg_read_compact_index(upkg->fhandle);
		fread(&upkg->imports[i].package_index, sizeof(int32_t), 1, upkg->fhandle);
		upkg->imports[i].object_name = upkg_read_compact_index(upkg->fhandle);
	}

	// allocate exports
	upkg->exports = (uexport_t *)calloc(upkg->num_exports, sizeof(uexport_t));

	// read in exports
	fseek(upkg->fhandle, upkg->ofs_exports, SEEK_SET);
	for (i = 0; i < upkg->num_exports; i++)
	{
		upkg->exports[i].class_index = upkg_read_compact_index(upkg->fhandle);
		upkg->exports[i].super_index = upkg_read_compact_index(upkg->fhandle);
		fread(&upkg->exports[i].package_index, sizeof(int32_t), 1, upkg->fhandle);
		upkg->exports[i].object_name = upkg_read_compact_index(upkg->fhandle);
		fread(&upkg->exports[i].object_flags, sizeof(uint32_t), 1, upkg->fhandle);
		upkg->exports[i].len_serial = upkg_read_compact_index(upkg->fhandle);

		if (upkg->exports[i].len_serial > 0)
			upkg->exports[i].ofs_serial = upkg_read_compact_index(upkg->fhandle);

		upkg->exports[i].pos = 0;
	}

	return upkg;
}

// free all memory associated with a upackage struct
static void upkg_close(upackage_t *upkg)
{
	if (upkg)
	{
		if (upkg->generations)
			free(upkg->generations);

		if (upkg->names)
		{
			for (int i = 0; i < upkg->num_names; i++)
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

		if (upkg->fhandle)
			fclose(upkg->fhandle);

		free(upkg);
	}
}

//
// utility functions
//

// read unreal engine compact index
static int32_t upkg_read_compact_index(FILE *stream)
{
	if (stream == NULL) return 0;

	int32_t ret = 0;
	uint8_t x;
	int sign = 1;

	for (int i = 0; i < 5; i++)
	{
		fread(&x, sizeof(uint8_t), 1, stream);

		if (i == 0)
		{
			//
			// first byte
			//

			// bit: X0000000
			if ((x & 0x80) > 0)
				sign = -1;

			// bits: 00XXXXXX
			ret |= (x & 0x3F);

			// bit: 0X000000
			if ((x & 0x40) == 0)
				break;
		}
		else if (i == 4)
		{
			//
			// last byte
			//

			// bits: 000XXXXX -- the 0 bits are ignored
			// (hits the 32 bit boundary)
			ret |= (x & 0x1F) << (6 + (3 * 7));
		}
		else
		{
			//
			// middle bytes
			//

			// bits: 0XXXXXXX
			ret |= (x & 0x7F) << (6 + ((i - 1) * 7));

			// bit: X0000000
			if ((x & 0x80) == 0)
				break;
		}
	}

	// multiply by the sign
	ret *= sign;

	// return the unpacked integer
	return ret;
}

// print all members of a upackage
static void upkg_print_members(upackage_t *upkg, FILE *stream)
{
	if (!upkg || !stream) return;

	int i;

	fprintf(stream, "\n");
	fprintf(stream, "|______upkg______|\n");
	fprintf(stream, "\n");

	// print header
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

	// print generations
	fprintf(stream, "\n\n");
	fprintf(stream, "|___generations table___|\n");
	fprintf(stream, "\n\n");

	for (i = 0; i < upkg->num_generations; i++)
	{
		fprintf(stream, "generation[%d].num_exports: %d\n", i, upkg->generations[i].num_exports);
		fprintf(stream, "generation[%d].num_names: %d\n", i, upkg->generations[i].num_names);
		fprintf(stream, "\n");
	}

	// print names
	fprintf(stream, "\n");
	fprintf(stream, "|___name table___|\n");
	fprintf(stream, "\n\n");

	for (i = 0; i < upkg->num_names; i++)
	{
		fprintf(stream, "names[%d]: %s\n", i, upkg->names[i].name);
	}

	// print imports
	fprintf(stream, "\n\n");
	fprintf(stream, "|___import table___|\n");
	fprintf(stream, "\n\n");

	for (i = 0; i < upkg->num_imports; i++)
	{
		fprintf(stream, "imports[%d]\n", i);
		fprintf(stream, "\tclass_package: %d\n", upkg->imports[i].class_package);
		fprintf(stream, "\tclass_name: %d\n", upkg->imports[i].class_name);
		fprintf(stream, "\tpackage_index: %d\n", upkg->imports[i].package_index);
		fprintf(stream, "\tobject_name: [%d]: %s\n", upkg->imports[i].object_name, upkg->names[upkg->imports[i].object_name].name);
		fprintf(stream, "\n");
	}

	// print exports
	fprintf(stream, "\n");
	fprintf(stream, "|___export table___|\n");
	fprintf(stream, "\n\n");

	for (i = 0; i < upkg->num_exports; i++)
	{
		fprintf(stream, "exports[%d]\n", i);
		fprintf(stream, "\tclass_index: %d\n", upkg->exports[i].class_index);
		fprintf(stream, "\tsuper_index: %d\n", upkg->exports[i].super_index);
		fprintf(stream, "\tpackage_index: %d\n", upkg->exports[i].package_index);
		fprintf(stream, "\tobject_name: [%d] %s\n", upkg->exports[i].object_name, upkg->names[upkg->exports[i].object_name].name);
		fprintf(stream, "\tobject_flags: %u\n", upkg->exports[i].object_flags);
		fprintf(stream, "\tlen_serial: %d\n", upkg->exports[i].len_serial);
		fprintf(stream, "\tofs_serial: %u\n", upkg->exports[i].ofs_serial);
		fprintf(stream, "\n");
	}
}

//
// reading data from objects contained in a package
//

// works like fread, except relative to the export object specified with export_index
static size_t upkg_fread(void *dest, size_t size, size_t n, upackage_t *upkg, int export_index)
{
	if (!upkg->fhandle) return -1;
	if (export_index >= upkg->num_exports) return -2;
	if ((size * n) > upkg->exports[export_index].len_serial) return -3;

	// seek to position in file handle
	fseek(upkg->fhandle, upkg->exports[export_index].ofs_serial + upkg->exports[export_index].pos, SEEK_SET);

	// do an fread
	return fread(dest, size, n, upkg->fhandle);
}

// works like fseek, except relative to the export object specified with export_index
static int upkg_fseek(long offset, int whence, upackage_t *upkg, int export_index)
{
	if (!upkg->fhandle) return -1;
	if (export_index >= upkg->num_exports) return -2;

	switch (whence)
	{
		case SEEK_SET:
			upkg->exports[export_index].pos = offset;
			break;

		case SEEK_CUR:
			upkg->exports[export_index].pos += offset;
			break;

		case SEEK_END:
			upkg->exports[export_index].pos = upkg->exports[export_index].len_serial + offset;
			break;

		default:
			break;
	}

	// error checking
	if (upkg->exports[export_index].pos > upkg->exports[export_index].len_serial)
		upkg->exports[export_index].pos = upkg->exports[export_index].len_serial;

	if (upkg->exports[export_index].pos < 0)
		upkg->exports[export_index].pos = 0;

	return 0;
}

// works like ftell, except relative to the export object specified with export_index
static long upkg_ftell(upackage_t *upkg, int export_index)
{
	return upkg->exports[export_index].pos;
}

#ifdef __cplusplus
}
#endif

#endif // __LIBUPKG_H__
