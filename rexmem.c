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
 * file: rexmem.c
 *
 * authors: erysdren
 *
 * last modified: january 16 2023
 *
 * ********************************** */

/* rex */
#include "rexstd.h"
#include "rextypes.h"
#include "rexmem.h"

int main(int argc, char **argv)
{
	/* variables */
	mempool mp;
	uint8 *buf;

	/* create pool */
	mempool_createpool(&mp, 64 * sizeof(uint8), sizeof(uint8));

	/* allocate memory from pool */
	buf = (uint8 *)mempool_alloc(&mp, 32 * sizeof(uint8));

	buf[0] = 8;
	buf[31] = 17;

	printf("%u\n", buf[0]);
	printf("%u\n", buf[31]);

	/* clear pool */
	mempool_freepool(&mp);

	/* exit gracefully */
	return EXIT_SUCCESS;
}
