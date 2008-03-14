# Make processor dependent startup and libraries for STR91x

# $Id: Makefile,v 1.4 2008-03-14 15:17:31 cvs Exp $

ARMSRC		= ..

ARCH		= arm966e-s
MCU		= str912faw44

LIBOBJS		= conio.o cpu.o syscalls.o

# Build support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)

include $(ARMSRC)/include/ARM.mk
