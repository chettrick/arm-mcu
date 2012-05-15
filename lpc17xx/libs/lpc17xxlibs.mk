# Makefile for LPC17xx libraries imported from NXP and other sources

# $Id$

LIBSDIR		= $(ARMSRC)/lpc17xx/libs

# libs/lpc17xx.cmsis.driver.library/Core/CM3/DeviceSupport/NXP/LPC17xx/LPC17xx.h

# Definitions for the LPC17xx CMSIS library

LPC17XXLIBDIR	= $(LIBSDIR)/lpc17xx.cmsis.driver.library
CMSIS		= $(LPC17XXLIBDIR)/Core/CM3
DSPLIB		= $(LPC17XXLIBDIR)/Core/DSP_Lib
DRIVERS		= $(LPC17XXLIBDIR)/Drivers

CFLAGS		+= -I$(CMSIS)/CoreSupport
CFLAGS		+= -I$(CMSIS)/DeviceSupport/NXP/LPC17xx
CFLAGS		+= -I$(DRIVERS)/include
ifeq ($(WITH_DSPLIB), yes)
CFLAGS		+= -DARM_MATH_CM3 -I$(CMSIS)/../DSP_Lib/Include
endif

lpc17xxlibs:
	$(MAKE) $(CMSIS)/DeviceSupport/NXP/LPC17xx/system_LPC17xx.o
	for F in $(CMSIS)/CoreSupport/*.c ; do $(MAKE) $${F%.c}.o ; done
	for F in $(DRIVERS)/source/*.c ; do $(MAKE) $${F%.c}.o ; done
ifeq ($(WITH_DSPLIB), yes)
	for F in $(CMSIS)/../DSP_Lib/Source/Cortex-M4-M3/*/*.c ; do $(MAKE) $${F%.c}.o ; done
endif
	$(FIND) $(LPC17XXLIBDIR) -type f -name '*.o' -exec $(AR) crs lib$(MCU).a {} ";"
