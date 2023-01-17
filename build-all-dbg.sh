##=============================================================================
##
## MIT License
##
## Copyright (c) 2023 erysdren
##
## Permission is hereby granted, free of charge, to any person obtaining a copy
## of this software and associated documentation files (the "Software"), to
## deal in the Software without restriction, including without limitation the
## rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
## sell copies of the Software, and to permit persons to whom the Software is
## furnished to do so, subject to the following conditions:
##
## The above copyright notice and this permission notice shall be included in
## all copies or substantial portions of the Software.
##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
## AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
## FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
## IN THE SOFTWARE.
##
##=============================================================================

##=========================================
##
## project: librex
##
## file: build-all-dbg.sh
##
## authors: erysdren
##
## last modified: january 17 2023
##
##=========================================

#!/bin/bash

## create build dir
if [ ! -d make-build-all-dbg ] 
then
	mkdir make-build-all-dbg
fi

## linux, gcc
make all DEBUG=1 LINUX_GCC=1
cp *_linux_gcc make-build-all-dbg/

## linux, watcom
make all DEBUG=1 LINUX_WATCOM=1
cp *_linux_watcom make-build-all-dbg/

## dos, djgpp
make all DEBUG=1 DOS_DJGPP=1
cp *.exe make-build-all-dbg/

## dos, watcom
make all DEBUG=1 DOS_WATCOM=1
cp *.exe make-build-all-dbg/

## windows, watcom
make all DEBUG=1 WINDOWS_WATCOM=1
cp *.exe make-build-all-dbg/

## win386, watcom
make all DEBUG=1 WIN386_WATCOM=1
cp *.exe make-build-all-dbg/

## windows, mingw
make all DEBUG=1 WINDOWS_MINGW=1
cp *.exe make-build-all-dbg/

## os/2, watcom
make all DEBUG=1 OS2_WATCOM=1
cp *.exe make-build-all-dbg/

## clean
make clean
