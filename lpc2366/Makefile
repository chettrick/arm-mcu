# Make processor dependent startup and libraries for LPC2366

# $Id: Makefile,v 1.6 2008-02-26 12:36:05 cvs Exp $

ARMSRC		= ..

ARCH		= arm7tdmi-s
MCU		= lpc2366

LIBOBJS		= conio.o cpu.o syscalls.o

# Build support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)

include $(ARMSRC)/include/ARM.mk
