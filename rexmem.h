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
 * file: rexmem.h
 *
 * authors: erysdren
 *
 * last modified: january 16 2023
 *
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_MEM_H__
#define __LIBREX_MEM_H__

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

/* *************************************
 *
 * the headers
 *
 * ********************************** */

/* rex */
#include "rexstd.h"
#include "rextypes.h"

/* *************************************
 *
 * the text macros
 *
 * ********************************** */

/* malloc */
#ifndef LIBREX_MALLOC
#define LIBREX_MALLOC(s) malloc(s)
#endif

/* realloc */
#ifndef LIBREX_REALLOC
#define LIBREX_REALLOC(p, s) realloc(p, s)
#endif

/* calloc */
#ifndef LIBREX_CALLOC
#define LIBREX_CALLOC(n, s) calloc(n, s)
#endif

/* free */
#ifndef LIBREX_FREE
#define LIBREX_FREE(p) free(p)
#endif

/* *************************************
 *
 * the types
 *
 * ********************************** */

/* mempool struct */
typedef struct mempool
{
	size_t min_alloc;
	size_t num_blocks;
	uint8 *next_free;
	uint8 *blocks;
} mempool;

/* *************************************
 *
 * the forward declarations
 *
 * ********************************** */

/* mempool creation and destruction */
void mempool_createpool(mempool *mp, size_t size, size_t min_alloc);
void mempool_freepool(mempool *mp);

/* allocate and free memory from pool */
void *mempool_alloc(mempool *mp, size_t size);
void mempool_free(mempool *mp, void *ptr);

/* *************************************
 *
 * the functions
 *
 * ********************************** */

/* 
 * mempool creation and destruction
 */

/* create a memory pool of s size */
void mempool_createpool(mempool *mp, size_t size, size_t min_alloc)
{
	/* sanity checks */
	assert(mp);

	/* set values */
	mp->num_blocks = size;
	mp->min_alloc = min_alloc;

	/* allocate memory */
	mp->blocks = (uint8 *)LIBREX_MALLOC(size * sizeof(uint8));
	if (!mp->blocks) return;

	/* set next free address to the start */
	mp->next_free = &mp->blocks[0];
}

/* free all memory used in a memory pool, leaving it ready for reuse */
void mempool_freepool(mempool *mp)
{
	/* sanity check */
	assert(mp);

	/* free memory */
	if (mp->blocks) LIBREX_FREE(mp->blocks);
}

/* 
 * allocate and free memory from pool
 */

/* allocate memory from pool */
void *mempool_alloc(mempool *mp, size_t size)
{
	/* variables */
	void *ret;

	/* sanity check */
	assert(mp);

	/* set return value to current free pointer */
	ret = (void *)mp->next_free;

	/* move the free pointer forwards */
	mp->next_free += size;

	/* return free pointer */
	return ret;
}

/* free memory in pool */
void mempool_free(mempool *mp, void *ptr)
{
	/* sanity check */
	assert(mp && ptr);
}

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_MEM_H__ */
