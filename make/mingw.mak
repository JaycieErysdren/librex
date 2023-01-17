## mingw prefix
ifndef MINGW_PREFIX
MINGW_PREFIX = x86_64-w64-mingw32-
endif

## mingw macros
CC = $(MINGW_PREFIX)gcc
CXX = $(MINGW_PREFIX)g++
LD = $(MINGW_PREFIX)ld
AR = $(MINGW_PREFIX)ar
AS = $(MINGW_PREFIX)as
STRIP = $(MINGW_PREFIX)strip
EXE = _windows_mingw.exe
