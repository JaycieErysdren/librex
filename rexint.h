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
 * last modified: january 18 2023
 * 
 * description: standard integer types
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

typedef signed char int8_t;				/* 8-bit signed int */
typedef unsigned char uint8_t;			/* 8-bit unsigned int */

typedef signed short int16_t;			/* 16-bit signed int */
typedef unsigned short uint16_t;		/* 16-bit unsigned int */

typedef signed long int32_t;			/* 32-bit signed int */
typedef unsigned long uint32_t;			/* 32-bit unsigned int */

typedef signed long long int64_t;		/* 64-bit signed int */
typedef unsigned long long uint64_t;	/* 64-bit unsigned int */

/* if, somehow, size_t is not defined */
#ifndef _SIZE_T
typedef uint32_t size_t;				/* size and stream offset */
#endif

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_INT_H__ */
