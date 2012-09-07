# Makefile for STM32F1 libraries imported from ST and other sources

# $Id$

LIBSDIR		= $(ARMSRC)/stm32f1/libs
CMSIS		= $(LIBSDIR)/CMSIS
DRIVERS		= $(LIBSDIR)/drivers

CFLAGS		+= -I$(CMSIS)/CM3/CoreSupport -I$(CMSIS)/CM3/DeviceSupport/ST/STM32F10x
CFLAGS		+= -DUSE_STDPERIPH_DRIVER -I$(DRIVERS)/inc

stm32f1libs:
	$(MAKE) $(CMSIS)/CM3/CoreSupport/core_cm3.o
	$(MAKE) $(CMSIS)/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.o
	for F in $(DRIVERS)/src/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(FIND) $(LIBSDIR) -type f -name '*.o' -exec $(AR) crs lib$(MCU).a {} ";"
