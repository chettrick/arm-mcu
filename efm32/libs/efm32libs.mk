# Makefile for EFM32 libraries imported from Engery Micro and other sources

# $Id$

LIBSDIR		= $(ARMSRC)/efm32/libs

# Definitions for the EFM32 CMSIS library

EFM32LIBVER	= 2.2.2
EFM32LIBNAME	= EFM32_CMSIS
EFM32LIBDIR	= $(LIBSDIR)/$(EFM32LIBNAME)_$(EFM32LIBVER)
CMSIS		= $(EFM32LIBDIR)/CMSIS/CM3
DSPLIB		= $(EFM32LIBDIR)/CMSIS/DSP_Lib
EFM32LIB	= $(EFM32LIBDIR)/efm32lib

CFLAGS		+= -I$(CMSIS)/CoreSupport
CFLAGS		+= -I$(CMSIS)/DeviceSupport/EnergyMicro/EFM32
CFLAGS		+= -I$(EFM32LIB)/inc
ifeq ($(WITH_DSPLIB), yes)
CFLAGS		+= -DARM_MATH_CM3 -I$(CMSIS)/../DSP_Lib/Include
endif

efm32libs:
	$(MAKE) $(CMSIS)/DeviceSupport/EnergyMicro/EFM32/system_efm32.o
	for F in $(CMSIS)/CoreSupport/*.c ; do $(MAKE) $${F%.c}.o ; done
	for F in $(EFM32LIB)/src/*.c ; do $(MAKE) $${F%.c}.o ; done
ifeq ($(WITH_DSPLIB), yes)
	for F in $(CMSIS)/../DSP_Lib/Source/Cortex-M4-M3/*/*.c ; do $(MAKE) $${F%.c}.o ; done
endif
	$(FIND) $(EFM32LIBDIR) -type f -name '*.o' -exec $(AR) crs lib$(MCU).a {} ";"
