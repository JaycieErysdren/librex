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
 * file: rexscalar.h
 *
 * authors: erysdren
 *
 * last modified: january 16 2023
 *
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_SCALAR_H__
#define __LIBREX_SCALAR_H__

/* options for fixed and floating point */
#define LIBREX_FIX16 1
#define LIBREX_FIX32 2
#define LIBREX_FLOAT32 3
#define LIBREX_FLOAT64 4

/* default base type to fixed */
#ifndef LIBREX_BASE_TYPE
#define LIBREX_BASE_TYPE LIBREX_FIX32
#endif

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

/* *************************************
 *
 * scalar types
 *
 * ********************************** */

/*
 * 32-bit fixed point scalar
 */

#if (LIBREX_BASE_TYPE == LIBREX_FIX32)

/* base type */
typedef fix32 scalar;

/* min, max, epsilon */
#define SCALAR_EPSILON FIX32_EPSILON
#define SCALAR_MIN FIX32_MIN
#define SCALAR_MAX FIX32_MAX

/* one */
#define SCALAR_ONE FIX32_ONE

/* static initialization macros */
#define SCALAR(a) FIX32(a)

/* math macros */
#define SCALAR_MUL(a, b) FIX32_MUL(a, b)
#define SCALAR_DIV(a, b) FIX32_DIV(a, b)
#define SCALAR_FLOOR(a) FIX32_FLOOR(a)
#define SCALAR_CEIL(a) FIX32_CEIL(a)
#define SCALAR_FRAC(a) FIX32_FRAC(a)
#define SCALAR_ROUND(a) FIX32_ROUND(a)

/* type conversion macros */
#define SCALAR_TO_INT(a) FIX32_TO_INT(a)
#define SCALAR_TO_FLOAT32(a) FIX32_TO_FLOAT32(a)
#define SCALAR_TO_FLOAT64(a) FIX32_TO_FLOAT64(a)

#endif /* LIBREX_BASE_TYPE == LIBREX_FIX32 */

/*
 * 16-bit fixed point scalar
 */

#if (LIBREX_BASE_TYPE == LIBREX_FIX16)

/* base type */
typedef fix16 scalar;

/* static initialization macros */
#define SCALAR(a) FIX16(a)

/* min, max, epsilon */
#define SCALAR_EPSILON FIX16_EPSILON
#define SCALAR_MIN FIX16_MIN
#define SCALAR_MAX FIX16_MAX

/* one */
#define SCALAR_ONE FIX16_ONE

/* math macros */
#define SCALAR_MUL(a, b) FIX16_MUL(a, b)
#define SCALAR_DIV(a, b) FIX16_DIV(a, b)
#define SCALAR_FLOOR(a) FIX16_FLOOR(a)
#define SCALAR_CEIL(a) FIX16_CEIL(a)
#define SCALAR_FRAC(a) FIX16_FRAC(a)
#define SCALAR_ROUND(a) FIX16_ROUND(a)

/* type conversion macros */
#define SCALAR_TO_INT(a) FIX16_TO_INT(a)
#define SCALAR_TO_FLOAT32(a) FIX16_TO_FLOAT32(a)
#define SCALAR_TO_FLOAT64(a) FIX16_TO_FLOAT64(a)

#endif /* LIBREX_BASE_TYPE == LIBREX_FIX16 */

/*
 * 32-bit floating point scalar
 */

#if (LIBREX_BASE_TYPE == LIBREX_FLOAT32)

/* base type */
typedef float32 scalar;

/* static initialization macros */
#define SCALAR(a) FLOAT32(a)

/* min, max, epsilon */
#define SCALAR_EPSILON FLT_EPSILON
#define SCALAR_MIN FLT_MAX
#define SCALAR_MAX FLT_MIN

/* one */
#define SCALAR_ONE 1.0f

/* math macros */
#define SCALAR_MUL(a, b) FLOAT32_MUL(a, b)
#define SCALAR_DIV(a, b) FLOAT32_DIV(a, b)
#define SCALAR_FLOOR(a) FLOAT32_FLOOR(a)
#define SCALAR_CEIL(a) FLOAT32_CEIL(a)
#define SCALAR_FRAC(a) FLOAT32_FRAC(a)
#define SCALAR_ROUND(a) FLOAT32_ROUND(a)

/* type conversion macros */
#define SCALAR_TO_INT(a) (a)
#define SCALAR_TO_FLOAT32(a) (a)
#define SCALAR_TO_FLOAT64(a) ((float64)(a))

#endif /* LIBREX_BASE_TYPE == LIBREX_FLOAT32 */

/*
 * 64-bit floating point scalar
 */

#if (LIBREX_BASE_TYPE == LIBREX_FLOAT64)

/* base type */
typedef float64 scalar;

/* static initialization macros */
#define SCALAR(a) FLOAT64(a)

/* min, max, epsilon */
#define SCALAR_EPSILON DBL_EPSILON
#define SCALAR_MIN DBL_MAX
#define SCALAR_MAX DBL_MIN

/* one */
#define SCALAR_ONE 1.0f

/* math macros */
#define SCALAR_MUL(a, b) FLOAT64_MUL(a, b)
#define SCALAR_DIV(a, b) FLOAT64_DIV(a, b)
#define SCALAR_FLOOR(a) FLOAT64_FLOOR(a)
#define SCALAR_CEIL(a) FLOAT64_CEIL(a)
#define SCALAR_FRAC(a) FLOAT64_FRAC(a)
#define SCALAR_ROUND(a) FLOAT64_ROUND(a)

/* type conversion macros */
#define SCALAR_TO_INT(a) (a)
#define SCALAR_TO_FLOAT32(a) ((float32)(a))
#define SCALAR_TO_FLOAT64(a) (a)

#endif /* LIBREX_BASE_TYPE == LIBREX_FLOAT64 */

/* *************************************
 *
 * math shortcut macros & etc
 *
 * ********************************** */

/* pi */
#ifndef PI
#define PI SCALAR(3.14159265358979323846)
#endif

/* return whatever value is lower */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/* return whatever value is higher */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/* clamp value to min and max */
#define CLAMP(a, min, max) MIN(MAX(a, min), max)

/* return absolute value */
#define ABS(a) (((a) < 0) ? -(a) : (a))

/* return sign */
#define SGN(a) (((a) < 0) ? -1 : (((a) > 0) ? 1 : 0))

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_SCALAR_H__ */
