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
 * file: rex.h
 *
 * authors: erysdren
 *
 * last modified: january 18 2023
 *
 * description: librex main header
 * 
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_H__
#define __LIBREX_H__

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

/* *************************************
 *
 * the headers
 *
 * ********************************** */

/* std */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <string.h>
#include <float.h>
#include <assert.h>
#include <stddef.h>

/*
 * djgpp doesn't allow stdint.h with c89
 * other compilers tend to be more leniant 
 */
#ifdef __DJGPP__
#include "rexint.h"
#else
#include <stdint.h>
#endif

/* rex: core */
#include "rexstd.h"
#include "rexmath.h"
#include "rexfloat.h"
#include "rexfixed.h"
#include "rexreal.h"
#include "rexmem.h"
#include "rexstring.h"
#include "rexcolor.h"
#include "rexbase64.h"
#include "rexbits.h"

/* rex: dos i/o */
#if defined(__DJGPP__) || defined(__WATCOMC__)
#include "rexdos.h"
#endif

/* rex: format i/o */
#include "rexupkg.h"

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_H__ */
