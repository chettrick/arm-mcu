# Makefile for STM32F1 libraries imported from ST and other sources

# $Id$

LIBSDIR		= $(ARMSRC)/stm32f1/libs

# libs/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h
# libs/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/CoreSupport/core_cm3.h
# libs/STM32F10x_StdPeriph_Lib_V3.5.0/Project/STM32F10x_StdPeriph_Template/stm32f10x_conf.h
# libs/STM32F10x_StdPeriph_Lib_V3.5.0/Project/STM32F10x_StdPeriph_Template/system_stm32f10x.c

# Definitions for the STM32F4 Standard Peripheral Library

PERIPHLIBVER	= V3.5.0
PERIPHLIBNAME	= STM32F10x_StdPeriph_Lib
PERIPHLIBDIR	= $(LIBSDIR)/$(PERIPHLIBNAME)_$(PERIPHLIBVER)
CMSIS		= $(PERIPHLIBDIR)/Libraries/CMSIS/CM3
STM32F1LIB	= $(PERIPHLIBDIR)/Libraries/STM32F10x_StdPeriph_Driver
STM32F1TEMPLATE	= $(PERIPHLIBDIR)/Project/STM32F10x_StdPeriph_Template

CFLAGS		+= -DUSE_STDPERIPH_DRIVER -I$(STM32F1LIB)/inc -I$(STM32F1TEMPLATE)
CFLAGS		+= -I$(CMSIS)/Include -I$(CMSIS)/CoreSupport
CFLAGS		+= -I$(CMSIS)/Include -I$(CMSIS)/DeviceSupport/ST/STM32F10x

stm32f1libs:
	$(MAKE) $(STM32F1TEMPLATE)/system_stm32f10x.o
	for F in $(STM32F1LIB)/src/*.c ; do $(MAKE) $${F%.c}.o ; done
	find $(PERIPHLIBDIR) -type f -name '*.o' -exec $(AR) crs lib$(MCU).a {} ";"
