## watcom prefix
ifndef WATCOM_PREFIX
WATCOM_PREFIX = /usr/bin/watcom/binl64/
endif

## watcom macros
CC = $(WATCOM_PREFIX)wcl386
CXX = $(WATCOM_PREFIX)wpp386
LD = $(WATCOM_PREFIX)wlink
AR = $(WATCOM_PREFIX)wlib
AS = $(WATCOM_PREFIX)wasm
STRIP = $(WATCOM_PREFIX)wstrip
BIND = $(WATCOM_PREFIX)wbind
OBJ = .obj
LIB = .lib
OUT = -fe=

##
## platform switches
##

## watcom linux target
ifdef LINUX
EXE = _linux_watcom
CFLAGS = -bcl=linux -I$(WATCOM_PREFIX)../lh
endif

## watcom win nt target
ifdef WINDOWS
EXE = _windows_watcom.exe
CFLAGS = -bcl=nt -I$(WATCOM_PREFIX)../h
endif

## watcom win386 target
ifdef WIN386
EXE = _win386_watcom.rex
CFLAGS = -bcl=win386 -I$(WATCOM_PREFIX)../h
endif

## watcom dos target
ifdef DOS
EXE = _dos_watcom.exe
CFLAGS = -bcl=dos32x -I$(WATCOM_PREFIX)../h
endif

## watcom os/2 target
ifdef OS2
EXE = _os2_watcom.exe
CFLAGS = -bcl=os2v2 -I$(WATCOM_PREFIX)../h
endif

##
## mode switches
##

## debug mode
ifdef DEBUG
CFLAGS += -d3
endif

## release mode
ifdef RELEASE
CFLAGS += -d0 -ox
endif

## pedantic mode
ifdef PEDANTIC
CFLAGS += -wx
endif
