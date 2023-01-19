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
 * file: rexbase64.c
 *
 * authors: erysdren
 *
 * last modified: january 18 2023
 *
 * description: rexbase64.h test app
 * 
 * ********************************** */

/* std */
#include <stdlib.h>
#include <stdio.h>

/* rex */
#include "rexstring.h"
#include "rexbase64.h"

int main(int argc, char **argv)
{
	/* variables */
	string_t source, encoded, decoded;

	/* allocate strings */
	source = string_create("this is a string");

	/* encode base64 */
	encoded = base64_encode_string(&source);

	/* decode base64 */
	decoded = base64_decode_string(&encoded);

	/* print results */
	printf("source: ");
	string_print(&source);
	printf("\n");
	printf("encoded: ");
	string_print(&encoded);
	printf("\n");
	printf("decoded: ");
	string_print(&decoded);
	printf("\n");

	/* free memory */
	string_free(&source);
	string_free(&decoded);
	string_free(&encoded);

	/* exit gracefully */
	return EXIT_SUCCESS;
}
