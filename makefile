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
## file: makefile
##
## authors: erysdren
##
## last modified: january 18 2023
##
##=========================================

##
## platform target switches
##

## compile for linux with gcc
ifdef LINUX_GCC
LINUX = 1
include make/gcc.mak
endif

## compile for linux with clang
ifdef LINUX_CLANG
LINUX = 1
include make/clang.mak
endif

## compile for windows with mingw
ifdef WINDOWS_MINGW
WINDOWS = 1
include make/mingw.mak
endif

## compile for linux with watcom
ifdef LINUX_WATCOM
LINUX = 1
include make/watcom.mak
endif

## compile for dos with watcom
ifdef DOS_WATCOM
DOS = 1
include make/watcom.mak
endif

## compile for windows with watcom
ifdef WINDOWS_WATCOM
WINDOWS = 1
include make/watcom.mak
endif

## compile for win386 with watcom
ifdef WIN386_WATCOM
WIN386 = 1
include make/watcom.mak
endif

## compile for os/2 with watcom
ifdef OS2_WATCOM
OS2 = 1
include make/watcom.mak
endif

## compile for dos with djgpp
ifdef DOS_DJGPP
DOS = 1
include make/djgpp.mak
endif

## if all else fails, just assume gcc
ifndef LINUX_GCC
ifndef LINUX_CLANG
ifndef WINDOWS_MINGW
ifndef LINUX_WATCOM
ifndef DOS_WATCOM
ifndef WINDOWS_WATCOM
ifndef WIN386_WATCOM
ifndef OS2_WATCOM
ifndef DOS_DJGPP
LINUX = 1
include make/gcc.mak
endif
endif
endif
endif
endif
endif
endif
endif
endif

##
## targets
##

## compile all targets
all: clean \
	rexreal \
	rexcolor \
	rexmem \
	rexstring \
	rexupkg \
	rexbase64 \
	rexargs \
	$(if $(DOS), rexdos) \

## real numbers
rexreal:
	$(CC) $(CFLAGS) $(OUT)rexreal$(EXE) rexreal.c -I.
	$(if $(WIN386), $(BIND) rexreal$(EXE) -n)

## rgba colors
rexcolor:
	$(CC) $(CFLAGS) $(OUT)rexcolor$(EXE) rexcolor.c -I.
	$(if $(WIN386), $(BIND) rexcolor$(EXE) -n)

## memory management
rexmem:
	$(CC) $(CFLAGS) $(OUT)rexmem$(EXE) rexmem.c -I.
	$(if $(WIN386), $(BIND) rexmem$(EXE) -n)

## string management
rexstring:
	$(CC) $(CFLAGS) $(OUT)rexstring$(EXE) rexstring.c -I.
	$(if $(WIN386), $(BIND) rexstring$(EXE) -n)

## unreal 1 package format
rexupkg:
	$(CC) $(CFLAGS) $(OUT)rexupkg$(EXE) rexupkg.c -I.
	$(if $(WIN386), $(BIND) rexupkg$(EXE) -n)

## base64 encoding
rexbase64:
	$(CC) $(CFLAGS) $(OUT)rexbase64$(EXE) rexbase64.c -I.
	$(if $(WIN386), $(BIND) rexbase64$(EXE) -n)

## dos platform i/o
rexdos:
	$(CC) $(CFLAGS) $(OUT)rexdos$(EXE) rexdos.c -I.
	$(if $(WIN386), $(BIND) rexdos$(EXE) -n)

## arg parsing
rexargs:
	$(CC) $(CFLAGS) $(OUT)rexargs$(EXE) rexargs.c -I.
	$(if $(WIN386), $(BIND) rexargs$(EXE) -n)

## clean
clean:
	$(RM) *_linux_gcc
	$(RM) *_linux_watcom
	$(RM) *_linux_clang
	$(RM) *.exe *.obj *.o *.err *.rex
	$(RM) *.EXE *.OBJ *.O *.ERR *.REX
