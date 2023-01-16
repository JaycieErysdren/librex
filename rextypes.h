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
 * file: rextypes.h
 *
 * authors: erysdren
 *
 * last modified: january 16 2023
 *
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_TYPES_H__
#define __LIBREX_TYPES_H__

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
 * standard headers
 *
 * ********************************** */

/* rex */
#include "rexstd.h"

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
#define FLOAT32_FLOOR(a) ((int32)(a))
#define FLOAT32_CEIL(a) ((int32)(a) == (a) ? (a) : (int32)((a) + 1))
#define FLOAT32_FRAC(a) ((a) - (int32)(a))
#define FLOAT32_ROUND(a) ((int32)((a) < 0 ? (a) - 0.5 : (a) + 0.5))

/* 64-bit float math macros */
#define FLOAT64_MUL(a, b) ((a) * (b))
#define FLOAT64_DIV(a, b) ((a) / (b))
#define FLOAT64_FLOOR(a) ((int32)(a))
#define FLOAT64_CEIL(a) ((int32)(a) == (a) ? (a) : (int32)((a) + 1))
#define FLOAT64_FRAC(a) ((a) - (int32)(a))
#define FLOAT64_ROUND(a) ((int32)((a) < 0 ? (a) - 0.5 : (a) + 0.5))

/* *************************************
 *
 * fixed point types
 *
 * ********************************** */

typedef int32 fix32;				/* 32-bit signed fixed (15.16) */
typedef uint32 ufix32;				/* 32-bit unsigned fixed (16.16) */

typedef int16 frac32;				/* 32-bit signed fraction (0.15) */
typedef uint16 ufrac32;				/* 32-bit unsigned fraction (0.16) */

typedef int16 fix16;				/* 16-bit signed fixed (7.8) */
typedef uint16 ufix16;				/* 16-bit unsigned fixed (8.8) */

typedef int8 frac16;				/* 16-bit signed fraction (0.7) */
typedef uint8 ufrac16;				/* 16-bit unsigned fraction (0.8) */

/*
 * 32-bit fixed
 */

/* 32-bit fixed mins and maxs */
#define FIX32_EPSILON 0x0001
#define FIX32_MAX INT32_MAX
#define FIX32_MIN INT32_MIN
#define UFIX32_MAX UINT32_MAX
#define UFIX32_MIN UINT32_MIN

/* 32-bit fixed representation of one */
#define FIX32_ONE (1 << 16)
#define UFIX32_ONE (1 << 16)

/* 32-bit fixed masks */
#define FIX32_MASK (0xFFFF0000)
#define UFIX32_MASK (0xFFFF0000)

/* 32-bit fraction representation of one */
#define FRAC32_ONE (1 << 15)
#define UFRAC32_ONE (1 << 16)

/* 32-bit fraction masks */
#define FRAC32_MASK (0x0000FFFF)
#define UFRAC32_MASK (0x0000FFFF)

/* 32-bit fixed static initialization macros */
#define FIX32(a) ((fix32)(FIX32_ONE * (a)))
#define UFIX32(a) ((ufix32)(FIX32_ONE * (a)))

/* 32-bit fraction static initialization macros */
#define FRAC32(a) ((frac32)((FRAC32_ONE * (a)) >= FRAC32_ONE ? \
					FRAC32_ONE - 1 : FRAC32_ONE * (a)))
#define UFRAC32(a) ((ufrac32)((UFRAC32_ONE * (a)) >= UFRAC32_ONE ? \
					UFRAC32_ONE - 1 : UFRAC32_ONE * (a)))

/* 32-bit math macros */
#define FIX32_MUL(a, b) (((int64)(a) * (b)) >> 16)
#define FIX32_DIV(a, b) (((int64)(a) << 16) / (b))
#define FIX32_FLOOR(a) ((a) & FIX32_MASK)
#define FIX32_CEIL(a) ((((a) & FRAC32_MASK) == 0) ? (a) : \
					FIX32_FLOOR((a) + FIX32_ONE))
#define FIX32_FRAC(a) ((a) & FRAC32_MASK)
#define FIX32_ROUND(a) (((a) & FRAC32_MASK) < FIX32(0.5f) ? \
					FIX32_FLOOR(a) : FIX32_CEIL(a))

/*
 * 16-bit fixed
 */

/* 16-bit fixed mins and maxs */
#define FIX16_EPSILON 0x01
#define FIX16_MAX INT16_MAX
#define FIX16_MIN INT16_MIN
#define UFIX16_MAX UINT16_MAX
#define UFIX16_MIN UINT16_MIN

/* 16-bit fixed representation of one */
#define FIX16_ONE (1 << 8)
#define UFIX16_ONE (1 << 8)

/* 16-bit fixed masks */
#define FIX16_MASK (0xFF00)
#define UFIX16_MASK (0xFF00)

/* 16-bit fraction representation of one */
#define FRAC16_ONE (1 << 7)
#define UFRAC16_ONE (1 << 8)

/* 16-bit fraction masks */
#define FRAC16_MASK (0x00FF)
#define UFRAC16_MASK (0x00FF)

/* 16-bit fixed static initialization macros */
#define FIX16(a) ((fix16)(FIX16_ONE * (a)))
#define UFIX16(a) ((ufix16)(FIX16_ONE * (a)))

/* 16-bit fraction static initialization macros */
#define FRAC16(a) ((frac16)((FRAC16_ONE * (a)) >= FRAC16_ONE ? \
					FRAC16_ONE - 1 : FRAC16_ONE * (a)))
#define UFRAC16(a) ((ufrac16)((UFRAC16_ONE * (a)) >= UFRAC16_ONE ? \
					UFRAC16_ONE - 1 : UFRAC16_ONE * (a)))

/* 16-bit math macros */
#define FIX16_MUL(a, b) (((int32)(a) * (b)) >> 8)
#define FIX16_DIV(a, b) (((int32)(a) << 8) / (b))
#define FIX16_FLOOR(a) ((a) & FIX16_MASK)
#define FIX16_CEIL(a) ((((a) & FRAC16_MASK) == 0) ? (a) : \
					FIX16_FLOOR((a) + FIX16_ONE))
#define FIX16_FRAC(a) ((a) & FRAC16_MASK)
#define FIX16_ROUND(a) (((a) & FRAC16_MASK) > FIX16(0.5f) ? \
					FIX16_FLOOR(a) : FIX16_CEIL(a))

/* *************************************
 *
 * type conversion macros
 *
 * ********************************** */

/*
 * 32-bit fixed conversions
 */

/* 32-bit fixed to int */
#define FIX32_TO_INT(a) ((a) >> 16)

/* 32-bit fixed to 32-bit float */
#define FIX32_TO_FLOAT32(a) ((a) * (1.0f / (float32)FIX32_ONE))

/* 32-bit fixed to 64-bit float */
#define FIX32_TO_FLOAT64(a) ((a) * (1.0f / (float64)FIX32_ONE))

/* 32-bit fixed to 32-bit fraction */
#define FIX32_TO_FRAC32(a) ((frac32)((a) / 2))

/* 32-bit fraction to 32-bit float */
#define FRAC32_TO_FLOAT32(a) ((a) * (1.0f / (float32)FRAC32_ONE))

/* 32-bit fraction to 64-bit float */
#define FRAC32_TO_FLOAT64(a) ((a) * (1.0f / (float64)FRAC32_ONE))

/* 32-bit fraction to 32-bit fixed */
#define FRAC32_TO_FIX32(a) ((fix32)((a) * 2))

/*
 * 16-bit fixed conversions
 */

/* 16-bit fixed to int */
#define FIX16_TO_INT(a) ((a) >> 8)

/* 16-bit fixed to 32-bit float */
#define FIX16_TO_FLOAT32(a) ((a) * (1.0f / (float32)FIX16_ONE))

/* 16-bit fixed to 64-bit float */
#define FIX16_TO_FLOAT64(a) ((a) * (1.0f / (float64)FIX16_ONE))

/* 16-bit fixed to 16-bit fraction */
#define FIX16_TO_FRAC16(a) ((frac16)((a) / 2))

/* 16-bit fraction to 32-bit float */
#define FRAC16_TO_FLOAT32(a) ((a) * (1.0f / (float32)FRAC16_ONE))

/* 16-bit fraction to 64-bit float */
#define FRAC16_TO_FLOAT64(a) ((a) * (1.0f / (float64)FRAC16_ONE))

/* 16-bit fraction to 16-bit fixed */
#define FRAC16_TO_FIX16(a) ((fix16)((a) * 2))

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
 * 32-bit floating point scalar
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

#endif /* __LIBREX_TYPES_H__ */
