## djgpp prefix
ifndef DJGPP_PREFIX
DJGPP_PREFIX = i586-pc-msdosdjgpp-
endif

## djgpp macros
CC = $(DJGPP_PREFIX)gcc
CXX = $(DJGPP_PREFIX)g++
LD = $(DJGPP_PREFIX)ld
AR = $(DJGPP_PREFIX)ar
AS = $(DJGPP_PREFIX)as
STRIP = $(DJGPP_PREFIX)strip
EXE = _dos_djgpp.exe

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
