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
 * file: rexbits.h
 *
 * authors: erysdren
 *
 * last modified: january 18 2023
 * 
 * description: bit swapping macros
 *
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_BITS_H__
#define __LIBREX_BITS_H__

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

/* *************************************
 *
 * the headers
 *
 * ********************************** */

/* stdint */
#ifdef __DJGPP__
#include "rexint.h"
#else
#include <stdint.h>
#endif

/* *************************************
 *
 * the forward declarations
 *
 * ********************************** */

int16_t bitswap_int16(int16_t *val);
uint16_t bitswap_uint16(uint16_t *val);
int32_t bitswap_int32(int32_t *val);
uint32_t bitswap_uint32(uint32_t *val);
int64_t bitswap_int64(int64_t *val);
uint64_t bitswap_uint64(uint64_t *val);

/* *************************************
 *
 * the text macros
 *
 * ********************************** */

/* 16-bit int */
#define SWAP_INT16(a) bitswap_int16(&a)
#define SWAP_UINT16(a) bitswap_uint16(&a)

/* 32-bit int */
#define SWAP_INT32(a) bitswap_int32(&a)
#define SWAP_UINT32(a) bitswap_uint32(&a)

/* 64-bit int */
#define SWAP_INT64(a) bitswap_int64(&a)
#define SWAP_UINT64(a) bitswap_uint64(&a)

/* *************************************
 *
 * the functions
 *
 * ********************************** */

/* bit swap int16_t */
int16_t bitswap_int16(int16_t *val)
{
	assert(val);

	*val = (*val << 8) | ((*val >> 8) & 0xFF);

	return *val;
}

/* bit swap uint16_t */
uint16_t bitswap_uint16(uint16_t *val)
{
	assert(val);

	*val = (*val << 8) | (*val >> 8);

	return *val;
}

/* bit swap int32_t */
int32_t bitswap_int32(int32_t *val)
{
	int32_t out;

	assert(val);

	out = ((*val << 8) & 0xFF00FF00) | ((*val >> 8) & 0xFF00FF);
	*val = (out << 16) | ((out >> 16) & 0xFFFF);

	return *val;
}

/* bit swap uint32_t */
uint32_t bitswap_uint32(uint32_t *val)
{
	uint32_t out;

	assert(val);

	out = ((*val << 8) & 0xFF00FF00) | ((*val >> 8) & 0xFF00FF);
	*val = (out << 16) | (out >> 16);

	return *val;
}

/* bit swap int64_t */
int64_t bitswap_int64(int64_t *val)
{
	int64_t out;

	assert(val);

	out = ((*val << 8) & 0xFF00FF00FF00FF00ULL) | ((*val >> 8) & 0x00FF00FF00FF00FFULL);
	out = ((out << 16) & 0xFFFF0000FFFF0000ULL) | ((out >> 16) & 0x0000FFFF0000FFFFULL);
	*val = (out << 32) | ((out >> 32) & 0xFFFFFFFF);

	return *val;
}

/* bit swap uint64_t */
uint64_t bitswap_uint64(uint64_t *val)
{
	uint64_t out;

	assert(val);

	out = ((*val << 8) & 0xFF00FF00FF00FF00ULL) | ((*val >> 8) & 0x00FF00FF00FF00FFULL);
	out = ((out << 16) & 0xFFFF0000FFFF0000ULL) | ((out >> 16) & 0x0000FFFF0000FFFFULL);
	*val = (out << 32) | (out >> 32);

	return *val;
}

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_BITS_H__ */
