## clang prefix
ifndef CLANG_PREFIX
CLANG_PREFIX = 
endif

## clang macros
CC = $(CLANG_PREFIX)clang
CXX = $(CLANG_PREFIX)clang++
LD = $(CLANG_PREFIX)ld
AR = $(CLANG_PREFIX)ar
AS = $(CLANG_PREFIX)as
STRIP = $(CLANG_PREFIX)strip
EXE = _linux_clang

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
