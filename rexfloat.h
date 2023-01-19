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
 * file: rexfloat.h
 *
 * authors: erysdren
 *
 * last modified: january 18 2023
 *
 * description: float helper macros
 * 
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_FLOAT_H__
#define __LIBREX_FLOAT_H__

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

#ifdef __DJGPP__
#include "rexint.h"
#else
#include <stdint.h>
#endif

#endif

/* *************************************
 *
 * floating point types
 *
 * ********************************** */

typedef float float32;				/* 32-bit float */
typedef double float64;				/* 64-bit float */

/* 32-bit float static initialization macros */
#define FLOAT32(a) ((float32)(a))
#define FLOAT64(a) ((float64)(a))

/* 32-bit float math macros */
#define FLOAT32_MUL(a, b) ((a) * (b))
#define FLOAT32_DIV(a, b) ((a) / (b))
#define FLOAT32_FLOOR(a) ((int32_t)(a))
#define FLOAT32_CEIL(a) ((int32_t)(a) == (a) ? (a) : (int32_t)((a) + 1))
#define FLOAT32_FRAC(a) ((a) - (int32_t)(a))
#define FLOAT32_ROUND(a) ((int32_t)((a) < 0 ? (a) - 0.5 : (a) + 0.5))

/* 64-bit float math macros */
#define FLOAT64_MUL(a, b) ((a) * (b))
#define FLOAT64_DIV(a, b) ((a) / (b))
#define FLOAT64_FLOOR(a) ((int64_t)(a))
#define FLOAT64_CEIL(a) ((int64_t)(a) == (a) ? (a) : (int64_t)((a) + 1))
#define FLOAT64_FRAC(a) ((a) - (int64_t)(a))
#define FLOAT64_ROUND(a) ((int64_t)((a) < 0 ? (a) - 0.5 : (a) + 0.5))

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_FLOAT_H__ */
