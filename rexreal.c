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
 * file: rexreal.c
 *
 * authors: erysdren
 *
 * last modified: january 18 2023
 * 
 * description: rexreal.h test app
 *
 * ********************************** */

/* std */
#include <stdio.h>
#include <stdlib.h>

/* rex */
#include "rexreal.h"

int main(int argc, char **argv)
{
	/* variables */
	real_t t1, t2, t3, t4, t5, t6, t7;

	/* set values */
	t1 = REAL(2.5f);
	t2 = REAL(8.0f);
	t3 = REAL_MUL(t2, t1);
	t4 = REAL_DIV(t2, t1);
	t5 = REAL_FLOOR(t1);
	t6 = REAL_CEIL(t1);
	t7 = REAL_ROUND(t1);

	/* print results */
	printf("t1: %0.4f\n", REAL_TO_FLOAT32(t1));
	printf("t2: %0.4f\n", REAL_TO_FLOAT32(t2));
	printf("t2 * t1: %0.4f\n", REAL_TO_FLOAT32(t3));
	printf("t2 / t1: %0.4f\n", REAL_TO_FLOAT32(t4));
	printf("floor(t1): %0.4f\n", REAL_TO_FLOAT32(t5));
	printf("ceil(t1): %0.4f\n", REAL_TO_FLOAT32(t6));
	printf("round(t1): %0.4f\n", REAL_TO_FLOAT32(t7));

	/* exit gracefully */
	return EXIT_SUCCESS;
}
