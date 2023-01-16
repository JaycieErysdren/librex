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
 * file: rexint.h
 *
 * authors: erysdren
 *
 * last modified: january 16 2023
 *
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_INT_H__
#define __LIBREX_INT_H__

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

/* *************************************
 *
 * integer types
 *
 * ********************************** */

/*
 * on the use of stdint.h types here:
 * may not be 100% portable if you're targeting
 * pre-C99 platforms. please investigate further!
 */

typedef int8_t int8;				/* 8-bit signed int */
typedef uint8_t uint8;				/* 8-bit unsigned int */

typedef int16_t int16;				/* 16-bit signed int */
typedef uint16_t uint16;			/* 16-bit unsigned int */

typedef int32_t int32;				/* 32-bit signed int */
typedef uint32_t uint32;			/* 32-bit unsigned int */

typedef int64_t int64;				/* 64-bit signed int */
typedef uint64_t uint64;			/* 64-bit unsigned int */

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_INT_H__ */
