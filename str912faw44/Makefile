# Make processor dependent startup and libraries for STR91x

# $Id: Makefile,v 1.5 2008-06-26 16:49:12 cvs Exp $

ARMSRC		= ..

ARCH		= arm966e-s
MCU		= str912faw44

LIBOBJS		= conio.o cpu.o syscalls.o

# Build support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(FWLIB)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(FWLIB)/*.o

include $(ARMSRC)/include/ARM.mk
