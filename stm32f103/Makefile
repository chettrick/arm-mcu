# Make processor dependent startup and libraries for STM32F10x

# $Id: Makefile,v 1.5 2008-07-01 18:12:00 cvs Exp $

ARMSRC		= ..

ARCH		= cortex-m3 -mthumb
MCU		= stm32f103

LIBOBJS		= conio.o cpu.o syscalls.o
FWLIB		= $(MCUDEPENDENT)/FWLib

CFLAGS		+= -I$(FWLIB)

# Build support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(FWLIB)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(FWLIB)/*.o

# Remove working files

clean_$(MCU):
	-rm *.a *.o $(FWLIB)/*.o

include $(ARMSRC)/include/ARM.mk
