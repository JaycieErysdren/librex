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
 * file: rexsurface.c
 *
 * authors: erysdren
 *
 * last modified: february 1 2023
 * 
 * description: rexsurface.h testapp
 *
 * ********************************** */

/* std */
#include <stdlib.h>
#include <stdio.h>

/* rex */
#include "rexsurface.h"

int main(int argc, char **argv)
{
	/* variables */
	surface_t *s1, *s2;
	color_t red, black;

	/* create surface */
	s1 = surface_create(64, 64, 32, NULL);

	/* create colors */
	color_set_argb8888(&red, 255, 0, 255, 255);
	color_set_argb8888(&black, 0, 0, 0, 255);

	/* clear surface */
	surface_clear(s1, &black);
	surface_borderbox(s1, 32, 32, 16, 16, &red);

	/* duplicate s1 to s2 */
	s2 = surface_duplicate(s1);

	/* save surface */
	surface_dump_buffer(s1, "test1.data");
	surface_dump_buffer(s2, "test2.data");

	/* destroy surface */
	surface_destroy(s1);
	surface_destroy(s2);

	/* exit gracefully */
	return EXIT_SUCCESS;
}
