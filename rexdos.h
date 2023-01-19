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
 * file: rexdos.h
 *
 * authors: erysdren
 *
 * last modified: january 18 2023
 *
 * description: dos platform i/o
 * 
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_DOS_H__
#define __LIBREX_DOS_H__

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * this file is special. we need to trigger a failure
 * if its not being compiled by a supported dos compiler
 */
#if !defined(__DJGPP__) && !defined(__WATCOMC__)
#error "rexdos.h can only be compiled with watcom or djgpp!"
#endif

/* *************************************
 *
 * the headers
 *
 * ********************************** */

/* if we're included outside of rex.h */
#ifndef __LIBREX_H__

/* std */
#ifdef __DJGPP__
#include "rexint.h"
#else
#include <stdint.h>
#endif

/* rex */
#include "rexstd.h"

#endif

/* dos headers */
#if defined(__DJGPP__) || defined(__WATCOMC__)

/* standard dos headers */
#include <dos.h>
#include <io.h>
#include <conio.h>

#endif

/* watcom headers */
#ifdef __WATCOMC__

#include <i86.h>
#include <graph.h>

#endif

/* djgpp headers */
#ifdef __DJGPP__

#include <dpmi.h>
#include <go32.h>
#include <sys/nearptr.h>
#include <sys/farptr.h>

#endif

/* *************************************
 *
 * the types
 *
 * ********************************** */



/* *************************************
 *
 * the forward declarations
 *
 * ********************************** */

static void dos_setvidmode(uint16_t mode);

/* *************************************
 *
 * the functions
 *
 * ********************************** */



#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_DOS_H__ */
