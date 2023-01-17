## gcc prefix
ifndef GCC_PREFIX
GCC_PREFIX = x86_64-linux-gnu-
endif

## gcc macros
CC = $(GCC_PREFIX)gcc
CXX = $(GCC_PREFIX)g++
LD = $(GCC_PREFIX)ld
AR = $(GCC_PREFIX)ar
AS = $(GCC_PREFIX)as
STRIP = $(GCC_PREFIX)strip
EXE = _linux_gcc

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
