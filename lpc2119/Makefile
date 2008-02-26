# Make processor dependent startup and libraries for LPC2119

# $Id: Makefile,v 1.9 2008-02-26 12:36:04 cvs Exp $

ARMSRC		= ..

ARCH		= arm7tdmi-s
MCU		= lpc2119

LIBOBJS		= conio.o cpu.o syscalls.o

# Build support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)

include $(ARMSRC)/include/ARM.mk
