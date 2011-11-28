# Processor dependent make definitions

# $Id$

CPU		= cortex-m3
CPUFLAGS	= -mthumb
TEXTBASE	?= 0x00000000

CMSIS		= $(MCUDIR)/CMSIS

CFLAGS		+= -DEFM32 -I$(CMSIS)/include
LDFLAGS		+= -Ttext $(TEXTBASE)

# Board specific macro definitions

ifeq ($(BOARDNAME), EFM32_G8XX_STK)
MCU		= efm32g890f128
endif

# Include MCU specific make file

include $(MCU).mk

# Phony targets

.PHONY:		default lib clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU)

default: lib

# Build processor dependent support library

LIBOBJS		= cpu.o gpiopins.o leds.o serial.o

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(CMSIS)/source/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(CMSIS)/source/*.o
	$(MAKE) otherlibs

lib: lib$(MCU).a

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
