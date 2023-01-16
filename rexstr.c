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
 * file: rexstr.c
 *
 * authors: erysdren
 *
 * last modified: january 16 2023
 *
 * ********************************** */

/* rex */
#include "rexstr.h"

int main(int argc, char **argv)
{
	/* variables */
	string s1, s2;
	FILE *file;

	/* open a text file */
	file = fopen("rexstr.h", "r");
	if (!file) return EXIT_FAILURE;

	/* allocate string for the job */
	s1 = string_alloc(16);
	s2 = string_createf("formatted string: %d\n", 15);

	/* print result */
	string_print(&s2);

	/* read string from file */
	string_reads(&s1, file, s1.len, '\n');

	/* print result */
	string_print(&s1);

	/* string insert */
	string_insert(&s1, &s2, 0);

	/* print result */
	string_print(&s2);

	/* free memory */
	string_free(&s1);
	string_free(&s2);

	/* close file handle */
	fclose(file);

	/* exit gracefully */
	return EXIT_SUCCESS;
}
