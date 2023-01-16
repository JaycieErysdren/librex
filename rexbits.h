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
 * last modified: january 16 2023
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
 * the forward declarations
 *
 * ********************************** */

int16 bitswap_int16(int16 *val);
uint16 bitswap_uint16(uint16 *val);
int32 bitswap_int32(int32 *val);
uint32 bitswap_uint32(uint32 *val);
int64 bitswap_int64(int64 *val);
uint64 bitswap_uint64(uint64 *val);

/* *************************************
 *
 * the functions
 *
 * ********************************** */

/* bit swap int16 */
int16 bitswap_int16(int16 *val)
{
	assert(val);

	*val = (*val << 8) | ((*val >> 8) & 0xFF);

	return *val;
}

/* bit swap uint16 */
uint16 bitswap_uint16(uint16 *val)
{
	assert(val);

	*val = (*val << 8) | (*val >> 8);

	return *val;
}

/* bit swap int32 */
int32 bitswap_int32(int32 *val)
{
	int32 out;

	assert(val);

	out = ((*val << 8) & 0xFF00FF00) | ((*val >> 8) & 0xFF00FF);
	*val = (out << 16) | ((out >> 16) & 0xFFFF);

	return *val;
}

/* bit swap uint32 */
uint32 bitswap_uint32(uint32 *val)
{
	uint32 out;

	assert(val);

	out = ((*val << 8) & 0xFF00FF00) | ((*val >> 8) & 0xFF00FF);
	*val = (out << 16) | (out >> 16);

	return *val;
}

/* bit swap int64 */
int64 bitswap_int64(int64 *val)
{
	int64 out;

	assert(val);

	out = ((*val << 8) & 0xFF00FF00FF00FF00) | ((*val >> 8) & 0x00FF00FF00FF00FF);
	out = ((out << 16) & 0xFFFF0000FFFF0000) | ((out >> 16) & 0x0000FFFF0000FFFF);
	*val = (out << 32) | ((out >> 32) & 0xFFFFFFFF);

	return *val;
}

/* bit swap uint64 */
uint64 bitswap_uint64(uint64 *val)
{
	uint64 out;

	assert(val);

	out = ((*val << 8) & 0xFF00FF00FF00FF00U) | ((*val >> 8) & 0x00FF00FF00FF00FFU);
	out = ((out << 16) & 0xFFFF0000FFFF0000U) | ((out >> 16) & 0x0000FFFF0000FFFFU);
	*val = (out << 32) | (out >> 32);

	return *val;
}

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_BITS_H__ */
