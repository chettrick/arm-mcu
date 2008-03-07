# Make processor dependent startup and libraries for STM32F10x

# $Id: Makefile,v 1.1 2008-03-07 13:51:19 cvs Exp $

ARMSRC		= ..

ARCH		= cortex-m3
MCU		= stm32f103

LIBOBJS		= conio.o cpu.o syscalls.o
FWLIB		= $(MCUDEPENDENT)/FWLib

# Build support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(FWLIB)/*.c ; do make $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(FWLIB)/*.o

include M3.mk
