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
 * file: rexstd.h
 *
 * authors: erysdren
 *
 * last modified: january 18 2023
 * 
 * description: global librex helpers
 *
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_STD_H__
#define __LIBREX_STD_H__

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

/* *************************************
 *
 * the headers
 *
 * ********************************** */

/* if we're included outside of rex.h */
#ifndef __LIBREX_H__

/* std */
#include <string.h>
#include <stdio.h>

#endif

/* *************************************
 *
 * text macros
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
 * gcc attributes
 *
 * ********************************** */

/* only enable in gcc-like compilers */
#if defined(__GNUC__) || defined(__DJGPP__)

#define ATTR_PACKED __attribute__((packed))

#else

#define ATTR_PACKED

#endif

/* *************************************
 *
 * types
 *
 * ********************************** */

/* fputc function which can be defined by the user */
typedef int (*librex_putf)(int c, FILE *stream);

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_STD_H__ */
