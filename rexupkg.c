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
 * file: rexupkg.c
 *
 * authors: erysdren
 *
 * last modified: january 18 2023
 * 
 * description: rexupkg.h test app
 *
 * ********************************** */

/* std */
#include <stdlib.h>
#include <stdio.h>

/* rex */
#include "rexupkg.h"

int main(int argc, char **argv)
{
	/* variables */
	upkg_t *upkg;

	/* if no args specified */
	if (argc < 2)
	{
		fprintf(stderr, "error: no file specified\n");
		return EXIT_FAILURE;
	}

	/* open upkg */
	upkg = upkg_open(argv[1]);

	if (upkg == NULL)
	{
		fprintf(stderr, "error: couldn't parse upackage file\n");
		return EXIT_FAILURE;
	}

	/* print member details */
	upkg_print_members(upkg, stdout);

	/* close upkg */
	upkg_close(upkg);

	/* exit gracefully */
	return EXIT_SUCCESS;
}
