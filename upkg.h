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
	int32_t num_exports;
	int32_t num_names;
} ugeneration_t;

// uname
typedef struct
{
	uint8_t len_name;
	char *name;
	uint32_t flags;
} uname_t;

// uexport
typedef struct
{
	int32_t class_index;	// compact index
	int32_t super_index;	// compact index
	int32_t package_index;
	int32_t object_name;	// compact index
	uint32_t object_flags;
	int32_t len_serial;		// compact index
	int32_t ofs_serial;		// compact index
} uexport_t;

// uimport
typedef struct
{
	int32_t class_package;	// compact index
	int32_t class_name;		// compact index
	int32_t package_index;
	int32_t object_name;	// compact index
} uimport_t;

// upackage
typedef struct
{
	// header
	// read this linearly from the top of the file

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

	// tables
	// seek to the appropriate offsets to get these

	uname_t *names;
	uexport_t *exports;
	uimport_t *imports;

	// misc
	//

	FILE *handle;

} upackage_t;

//=========================================
//
// the functions
//
//=========================================

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
			// First byte

			// Bit: X0000000
			if ((x & 0x80) > 0)
				sign = -1;

			// Bits: 00XXXXXX
			ret |= (x & 0x3F);

			// Bit: 0X000000
			if ((x & 0x40) == 0)
				break;
		}
		else if (i == 4)
		{
			// Last byte

			// Bits: 000XXXXX -- the 0 bits are ignored
			// (hits the 32 bit boundary)
			ret |= (x & 0x1F) << (6 + (3 * 7));
		}
		else
		{
			// Middle bytes

			// Bits: 0XXXXXXX
			ret |= (x & 0x7F) << (6 + ((i - 1) * 7));

			// Bit: X0000000
			if ((x & 0x80) == 0)
				break;
		}
	}

	// multiply by negative one here, since the first 6+ bits could be 0
	ret *= sign;

	// return integer
	return ret;
}

// read upackage file and return a upackage struct
static upackage_t *upkg_create(const char *filename)
{
	int i;

	// open file handle
	FILE *file = fopen(filename, "rb");
	if (file == NULL) return NULL;

	// allocate struct
	upackage_t *upkg = (upackage_t *)calloc(1, sizeof(upackage_t));

	// read in header
	fread(upkg, offsetof(upackage_t, generations), 1, file);

	// check if tag is correct
	if (upkg->tag != 2653586369) return NULL;

	// allocate generations
	upkg->generations = (ugeneration_t *)calloc(upkg->num_generations, sizeof(ugeneration_t));

	// read in generations
	fread(upkg->generations, sizeof(ugeneration_t), upkg->num_generations, file);

	// allocate names
	upkg->names = (uname_t *)calloc(upkg->num_names, sizeof(uname_t));

	// read in names
	fseek(file, upkg->ofs_names, SEEK_SET);
	for (i = 0; i < upkg->num_names; i++)
	{
		fread(&upkg->names[i].len_name, sizeof(uint8_t), 1, file);
		upkg->names[i].name = (char *)calloc(upkg->names[i].len_name, sizeof(char));
		fread(upkg->names[i].name, sizeof(char), upkg->names[i].len_name, file);
		fread(&upkg->names[i].flags, sizeof(uint32_t), 1, file);
	}

	// allocate imports
	upkg->imports = (uimport_t *)calloc(upkg->num_imports, sizeof(uimport_t));

	// read in imports
	fseek(file, upkg->ofs_imports, SEEK_SET);
	for (i = 0; i < upkg->num_imports; i++)
	{
		upkg->imports[i].class_package = upkg_read_compact_index(file);
		upkg->imports[i].class_name = upkg_read_compact_index(file);
		fread(&upkg->imports[i].package_index, sizeof(int32_t), 1, file);
		upkg->imports[i].object_name = upkg_read_compact_index(file);
	}

	// allocate exports
	upkg->exports = (uexport_t *)calloc(upkg->num_exports, sizeof(uexport_t));

	// read in exports
	fseek(file, upkg->ofs_exports, SEEK_SET);
	for (i = 0; i < upkg->num_exports; i++)
	{
		upkg->exports[i].class_index = upkg_read_compact_index(file);
		upkg->exports[i].super_index = upkg_read_compact_index(file);
		fread(&upkg->exports[i].package_index, sizeof(int32_t), 1, file);
		upkg->exports[i].object_name = upkg_read_compact_index(file);
		fread(&upkg->exports[i].object_flags, sizeof(uint32_t), 1, file);
		upkg->exports[i].len_serial = upkg_read_compact_index(file);

		if (upkg->exports[i].len_serial > 0)
			upkg->exports[i].ofs_serial = upkg_read_compact_index(file);
	}

	// close file handle
	fclose(file);

	return upkg;
}

// free all memory associated with a upackage struct
static void upkg_destroy(upackage_t *upkg)
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

		if (upkg->handle)
			fclose(upkg->handle);

		free(upkg);
	}
}

#endif // __LIBUPKG_H__
