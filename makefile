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
## last modified: january 16 2023
##
##=========================================

CFLAGS += -std=c89 -pedantic -Wall -g -Wno-unused-function

all: rexscalar rexcolor rexmem rexstr rexupkg rexbase64

rexscalar:
	$(CC) $(CFLAGS) -o rexscalar rexscalar.c -I.

rexcolor:
	$(CC) $(CFLAGS) -o rexcolor rexcolor.c -I.

rexmem:
	$(CC) $(CFLAGS) -o rexmem rexmem.c -I.

rexstr:
	$(CC) $(CFLAGS) -o rexstr rexstr.c -I.

rexupkg:
	$(CC) $(CFLAGS) -o rexupkg rexupkg.c -I.

rexbase64:
	$(CC) $(CFLAGS) -o rexbase64 rexbase64.c -I.

clean:
	$(RM) rexscalar rexcolor rexmem rexstr rexupkg rexbase64
