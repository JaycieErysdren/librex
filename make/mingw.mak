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

OUT = -o
OBJ = .o
LIB = .a

## debug mode
ifdef DEBUG
CFLAGS += -g
endif

## release mode
ifdef RELEASE
CFLAGS += -O2 -s
endif

## pedantic mode
ifdef PEDANTIC
CFLAGS += -std=c89 -pedantic -Wall
endif

## pedantic mode (lite!)
ifdef PEDANTIC-LITE
CFLAGS += -std=c89 -pedantic -Wall -Wno-unused-function -Wno-long-long
endif
