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
	surface_t *surface;
	color_t red, black;

	/* create surface */
	surface = surface_create(64, 64, 32, NULL);

	/* create colors */
	color_set_argb8888(&red, 255, 0, 255, 255);
	color_set_argb8888(&black, 0, 0, 0, 255);

	/* clear surface */
	surface_clear(surface, &black);
	surface_borderbox(surface, 32, 32, 16, 16, &red);

	/* save surface */
	surface_dump_buffer(surface, "test.data");

	/* destroy surface */
	surface_destroy(surface);

	/* exit gracefully */
	return EXIT_SUCCESS;
}
