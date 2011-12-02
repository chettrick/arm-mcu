# Processor dependent make definitions

# $Id$

CPU		= cortex-m3
CPUFLAGS	= -mthumb
TEXTBASE	?= 0x00000000

CFLAGS		+= -DEFM32
LDFLAGS		+= -Ttext $(TEXTBASE)

# Board specific macro definitions

ifeq ($(BOARDNAME), EFM32_G8XX_STK)
MCU		= efm32g890f128
JLINKGDBIF	= -if SWD
endif

# Include MCU specific make file

include $(MCUDIR)/$(MCU).mk

# Phony targets

.PHONY:		lib clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU)

# Build processor dependent support library

include libs/efm32libs.mk

LIBOBJS		= cpu.o gpiopins.o leds.o serial.o

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	$(MAKE) efm32libs
	$(MAKE) otherlibs

lib: lib$(MCU).a

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
