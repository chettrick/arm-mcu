# Make processor dependent startup and libraries for STM32F10x

# $Id: Makefile,v 1.4 2008-06-26 15:56:25 cvs Exp $

ARMSRC		= ..

ARCH		= cortex-m3 -mthumb
MCU		= stm32f103

LIBOBJS		= conio.o cpu.o syscalls.o

# Build support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(FWLIB)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(FWLIB)/*.o

include $(ARMSRC)/include/ARM.mk
