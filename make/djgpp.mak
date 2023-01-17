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
