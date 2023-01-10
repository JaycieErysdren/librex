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
// file: example1.c
//
// authors: erysdren
//
// last modified: january 9 2023
//
//=========================================

// header
#include "upkg.h"

// print all members of a upackage
void upkg_print(FILE *stream, upackage_t *upkg)
{
	if (upkg == NULL) return;
	if (stream == NULL) return;

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

// program entry point
int main(int argc, char **argv)
{
	// if no args specified
	if (argc < 2)
	{
		fprintf(stderr, "error: no file specified\n");
		return EXIT_FAILURE;
	}

	// create upkg
	upackage_t *upkg = upkg_create(argv[1]);

	if (upkg == NULL)
	{
		printf("error: couldn't parse upackage file for some reason\n");
		return EXIT_FAILURE;
	}

	// print details
	upkg_print(stdout, upkg);

	// destroy upkg
	upkg_destroy(upkg);

	// return success
	return EXIT_SUCCESS;
}
