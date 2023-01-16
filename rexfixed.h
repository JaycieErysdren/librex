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
 * file: rexfixed.h
 *
 * authors: erysdren
 *
 * last modified: january 16 2023
 *
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_FIXED_H__
#define __LIBREX_FIXED_H__

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_FIXED_H__ */
