# librex

A collection of single-header C89 libraries to enhance your C programming experience.

## Directory

| Name			| Description												|
|---------------|-----------------------------------------------------------|
| rexstd.h 		| Include file for stdlib headers.							|
| rexint.h 		| Integer types.											|
| rexfloat.h 	| Floating-point types and operations.						|
| rexfixed.h 	| Fixed-point types and operations.							|
| rexreal.h 	| Interop between floating-point and fixed-point.			|
| rexmem.h 		| Basic memory pool implementation.							|
| rexstring.h 	| Small but powerful string library.						|
| rexcolor.h 	| RGB565 + RGBA8888 + ARGB8888 conversions.					|
| rexbase64.h 	| Base64 encoding and decoding of strings.					|
| rexbits.h 	| Bit swapping between big and little endianness.			|
| rexdos.h 		| DOS platform I/O. Supports both DJGPP and Open Watcom.	|

## Building

Navigate to the repository directory and type `make` in the terminal to build the test applications.

I've implemented a build system using GNU Make that supports various platform targets. Supported platforms are:

- Linux via GCC (`make LINUX_GCC=1`)
- Linux via Clang (`make LINUX_CLANG=1`)
- Linux x86 via Watcom (`make LINUX_WATCOM=1`)
- DOS32 via DJGPP (`make DOS_DJGPP=1`)
- DOS32 via Watcom (`make DOS_WATCOM=1`)
- Win32 via Watcom (`make WINDOWS_WATCOM=1`)
- Win386 via Watcom (`make WIN386_WATCOM=1`)
- Windows via MinGW (`make WINDOWS_MINGW=1`)
- OS/2 via Watcom (`make OS2_WATCOM=1`)

If no target is provided, Linux via GCC is assumed.

There are also various switches that can be used to enable or disable compile features. Those switches are:

- Debug mode (`make DEBUG=1`)
- Release mode (`make RELEASE=1`)
- Pedantic mode (`make PEDANTIC=1`)
- Pedantic mode (lite!) (`make PEDANTIC-LITE=1`)

## License

MIT License

Copyright (c) 2023 erysdren

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
