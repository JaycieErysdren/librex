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
 * file: rexreal.h
 *
 * authors: erysdren
 *
 * last modified: january 18 2023
 * 
 * description: fixed point to floating point interop
 *
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_REAL_H__
#define __LIBREX_REAL_H__

/* options for fixed and floating point */
#define LIBREX_FIX16 1
#define LIBREX_FIX32 2
#define LIBREX_FLOAT32 3
#define LIBREX_FLOAT64 4

/* default base real type to fixed32 */
#ifndef LIBREX_REAL_TYPE
#define LIBREX_REAL_TYPE LIBREX_FIX32
#endif

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

/* *************************************
 *
 * headers
 *
 * ********************************** */

/* if we're included outside of rex.h */
#ifndef __LIBREX_H__

/* rex */
#include "rexfixed.h"
#include "rexfloat.h"

#endif

/* *************************************
 *
 * real types
 *
 * ********************************** */

/*
 * 16-bit fixed point real
 */

#if (LIBREX_REAL_TYPE == LIBREX_FIX16)

/* base type */
typedef fix16 real_t;

/* static initialization macros */
#define REAL(a) FIX16(a)

/* min, max, epsilon */
#define REAL_EPSILON FIX16_EPSILON
#define REAL_MIN FIX16_MIN
#define REAL_MAX FIX16_MAX

/* one */
#define REAL_ONE FIX16_ONE

/* math macros */
#define REAL_MUL(a, b) FIX16_MUL(a, b)
#define REAL_DIV(a, b) FIX16_DIV(a, b)
#define REAL_FLOOR(a) FIX16_FLOOR(a)
#define REAL_CEIL(a) FIX16_CEIL(a)
#define REAL_FRAC(a) FIX16_FRAC(a)
#define REAL_ROUND(a) FIX16_ROUND(a)

/* type conversion macros */
#define REAL_TO_INT(a) FIX16_TO_INT(a)
#define REAL_TO_FIX16(a) (a)
#define REAL_TO_FIX32(a) ((fix32)(a))
#define REAL_TO_FLOAT32(a) FIX16_TO_FLOAT32(a)
#define REAL_TO_FLOAT64(a) FIX16_TO_FLOAT64(a)

#endif /* LIBREX_REAL_TYPE == LIBREX_FIX16 */

/*
 * 32-bit fixed point real
 */

#if (LIBREX_REAL_TYPE == LIBREX_FIX32)

/* base type */
typedef fix32 real_t;

/* min, max, epsilon */
#define REAL_EPSILON FIX32_EPSILON
#define REAL_MIN FIX32_MIN
#define REAL_MAX FIX32_MAX

/* one */
#define REAL_ONE FIX32_ONE

/* static initialization macros */
#define REAL(a) FIX32(a)

/* math macros */
#define REAL_MUL(a, b) FIX32_MUL(a, b)
#define REAL_DIV(a, b) FIX32_DIV(a, b)
#define REAL_FLOOR(a) FIX32_FLOOR(a)
#define REAL_CEIL(a) FIX32_CEIL(a)
#define REAL_FRAC(a) FIX32_FRAC(a)
#define REAL_ROUND(a) FIX32_ROUND(a)

/* type conversion macros */
#define REAL_TO_INT(a) FIX32_TO_INT(a)
#define REAL_TO_FIX16(a) ((fix16)(a))
#define REAL_TO_FIX32(a) (a)
#define REAL_TO_FLOAT32(a) FIX32_TO_FLOAT32(a)
#define REAL_TO_FLOAT64(a) FIX32_TO_FLOAT64(a)

#endif /* LIBREX_REAL_TYPE == LIBREX_FIX32 */

/*
 * 32-bit floating point real
 */

#if (LIBREX_REAL_TYPE == LIBREX_FLOAT32)

/* base type */
typedef float32 real_t;

/* static initialization macros */
#define REAL(a) FLOAT32(a)

/* min, max, epsilon */
#define REAL_EPSILON FLT_EPSILON
#define REAL_MIN FLT_MAX
#define REAL_MAX FLT_MIN

/* one */
#define REAL_ONE 1.0f

/* math macros */
#define REAL_MUL(a, b) FLOAT32_MUL(a, b)
#define REAL_DIV(a, b) FLOAT32_DIV(a, b)
#define REAL_FLOOR(a) FLOAT32_FLOOR(a)
#define REAL_CEIL(a) FLOAT32_CEIL(a)
#define REAL_FRAC(a) FLOAT32_FRAC(a)
#define REAL_ROUND(a) FLOAT32_ROUND(a)

/* type conversion macros */
#define REAL_TO_INT(a) (a)
#define REAL_TO_FIX16(a) FIX16(a)
#define REAL_TO_FIX32(a) FIX32(a)
#define REAL_TO_FLOAT32(a) (a)
#define REAL_TO_FLOAT64(a) ((float64)(a))

#endif /* LIBREX_REAL_TYPE == LIBREX_FLOAT32 */

/*
 * 64-bit floating point real
 */

#if (LIBREX_REAL_TYPE == LIBREX_FLOAT64)

/* base type */
typedef float64 real_t;

/* static initialization macros */
#define REAL(a) FLOAT64(a)

/* min, max, epsilon */
#define REAL_EPSILON DBL_EPSILON
#define REAL_MIN DBL_MAX
#define REAL_MAX DBL_MIN

/* one */
#define REAL_ONE 1.0f

/* math macros */
#define REAL_MUL(a, b) FLOAT64_MUL(a, b)
#define REAL_DIV(a, b) FLOAT64_DIV(a, b)
#define REAL_FLOOR(a) FLOAT64_FLOOR(a)
#define REAL_CEIL(a) FLOAT64_CEIL(a)
#define REAL_FRAC(a) FLOAT64_FRAC(a)
#define REAL_ROUND(a) FLOAT64_ROUND(a)

/* type conversion macros */
#define REAL_TO_INT(a) (a)
#define REAL_TO_FIX16(a) FIX16(a)
#define REAL_TO_FIX32(a) FIX32(a)
#define REAL_TO_FLOAT32(a) ((float32)(a))
#define REAL_TO_FLOAT64(a) (a)

#endif /* LIBREX_REAL_TYPE == LIBREX_FLOAT64 */

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_REAL_H__ */
