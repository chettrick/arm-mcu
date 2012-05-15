# Makefile for STM32F4 libraries imported from ST and other sources

# $Id$

LIBSDIR		= $(ARMSRC)/stm32f4/libs

# Definitions for the STM32F4 Standard Peripheral Library

PERIPHLIBVER	= V1.0.1
PERIPHLIBNAME	= STM32F4xx_DSP_StdPeriph_Lib
PERIPHLIBDIR	= $(LIBSDIR)/$(PERIPHLIBNAME)_$(PERIPHLIBVER)
CMSIS		= $(PERIPHLIBDIR)/Libraries/CMSIS
STM32F4LIB	= $(PERIPHLIBDIR)/Libraries/STM32F4xx_StdPeriph_Driver
STM32F4TEMPLATE	= $(PERIPHLIBDIR)/Project/STM32F4xx_StdPeriph_Templates

CFLAGS		+= -DUSE_STDPERIPH_DRIVER -I$(STM32F4LIB)/inc -I$(STM32F4TEMPLATE)
CFLAGS		+= -I$(CMSIS)/Include -I$(CMSIS)/Device/ST/STM32F4xx/Include
ifeq ($(WITH_DSPLIB), yes)
CFLAGS		+= -DARM_MATH_CM4
endif

stm32f4libs:
	$(MAKE) $(STM32F4TEMPLATE)/system_stm32f4xx.o
	for F in $(STM32F4LIB)/src/*.c ; do $(MAKE) $${F%.c}.o ; done
ifeq ($(WITH_DSPLIB), yes)
	for F in $(CMSIS)/DSP_Lib/Source/*/*.c ; do $(MAKE) $${F%.c}.o ; done
endif
	$(FIND) $(PERIPHLIBDIR) -type f -name '*.o' -exec $(AR) crs lib$(MCU).a {} ";"
