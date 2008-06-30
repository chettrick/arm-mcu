# Make processor dependent startup and libraries for STR91x

# $Id: Makefile,v 1.6 2008-06-30 14:36:07 cvs Exp $

ARMSRC		= ..

ARCH		= arm9
MCU		= str912faw44

LIBOBJS		= conio.o cpu.o syscalls.o

# Build support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(FWLIB)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(FWLIB)/*.o

include $(ARMSRC)/include/ARM.mk
