# Make processor dependent startup and libraries for STR91x

# $Id: Makefile,v 1.3 2008-02-26 12:36:05 cvs Exp $

ARMSRC		= ..

ARCH		= arm9
MCU		= str912faw44

LIBOBJS		= conio.o cpu.o syscalls.o

# Build support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)

include $(ARMSRC)/include/ARM.mk
