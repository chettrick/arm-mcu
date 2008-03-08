# Make processor dependent startup and libraries for STM32F10x

# $Id: Makefile,v 1.2 2008-03-08 07:22:38 cvs Exp $

ARMSRC		= ..

ARCH		= cortex-m3 -mthumb
MCU		= stm32f103
CC		= $(M3TOOLS)/bin/arm-none-eabi-gcc

LIBOBJS		= conio.o cpu.o syscalls.o
FWLIB		= $(MCUDEPENDENT)/FWLib

# Build support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(FWLIB)/*.c ; do make $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(FWLIB)/*.o

include $(ARMSRC)/include/ARM.mk
