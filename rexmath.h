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
 * file: rexmath.h
 *
 * authors: erysdren
 *
 * last modified: january 18 2023
 * 
 * description: math helper macros
 *
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_MATH_H__
#define __LIBREX_MATH_H__

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

/* *************************************
 *
 * the text macros
 *
 * ********************************** */

/* pi */
#ifndef PI
#define PI 3.14159265358979323846
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

#endif /* __LIBREX_MATH_H__ */
