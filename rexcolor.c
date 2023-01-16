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
 * file: rexcolor.c
 *
 * authors: erysdren
 *
 * last modified: january 15 2023
 *
 * ********************************** */

/* rex */
#include "rex.h"

int main(int argc, char **argv)
{
	/* variables */
	color c;

	/* print header */
	printf("librex: rexcolor.h test\n");
	printf("\n");

	/* test index8 setting and retrieval */
	color_set_index8(&c, 176);
	printf("type: index8\n");
	printf("input: 176\n");
	printf("\n");
	printf("results:\n");
	printf("\tindex8: %u\n", color_get_index8(&c));

	printf("\n");
	printf("\n");

	/* test rgb565 setting and retrieval */
	color_set_rgb565(&c, 125, 76, 253);
	printf("type: rgb565\n");
	printf("input: 125, 76, 253\n");
	printf("\n");
	printf("results:\n");
	printf("\tred: %u\n", color_get_red(&c));
	printf("\tgreen: %u\n", color_get_green(&c));
	printf("\tblue: %u\n", color_get_blue(&c));

	printf("\n");
	printf("\n");

	/* test rgba8888 setting and retrieval */
	color_set_rgba8888(&c, 57, 78, 14, 255);
	printf("type: rgba8888\n");
	printf("input: 57, 78, 14, 255\n");
	printf("\n");
	printf("results:\n");
	printf("\tred: %u\n", color_get_red(&c));
	printf("\tgreen: %u\n", color_get_green(&c));
	printf("\tblue: %u\n", color_get_blue(&c));
	printf("\talpha: %u\n", color_get_alpha(&c));

	printf("\n");
	printf("\n");

	/* test argb8888 setting and retrieval */
	color_set_argb8888(&c, 17, 93, 232, 127);
	printf("type: argb8888\n");
	printf("input: 17, 93, 232, 127\n");
	printf("\n");
	printf("results:\n");
	printf("\tred: %u\n", color_get_red(&c));
	printf("\tgreen: %u\n", color_get_green(&c));
	printf("\tblue: %u\n", color_get_blue(&c));
	printf("\talpha: %u\n", color_get_alpha(&c));

	printf("\n");

	/* test float retrieval */
	printf("results (float):\n");
	printf("\tred: %0.4f\n", color_get_redf(&c));
	printf("\tgreen: %0.4f\n", color_get_greenf(&c));
	printf("\tblue: %0.4f\n", color_get_bluef(&c));
	printf("\talpha: %0.4f\n", color_get_alphaf(&c));

	/* exit gracefully */
	return EXIT_SUCCESS;
}
