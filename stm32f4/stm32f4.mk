# STM32F4 family make definitions

# $Id: stm32.mk 3236 2011-11-03 11:31:27Z svn $

CPU		= cortex-m4
CPUFLAGS	= -mthumb
FLASHWRITEADDR	= 0x08000000
TEXTBASE	?= 0x00000000

CFLAGS		+= -DSTM32F4XX
LDFLAGS		+= -Ttext $(TEXTBASE)

# Board specific macro definitions

ifeq ($(BOARDNAME), STM32F4_DISCOVERY)
CFLAGS		+= -DHSE_VALUE=8000000
MCU		= stm32f407vg
JLINKGDBIF	= -if SWD

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
STLINKIF	= -c SWD
endif
endif

# Phony targets

.PHONY:		clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU) lib

# Build processor dependent support library

include $(MCUDIR)/libs/stm32f4libs.mk

LIBOBJS		= cpu.o gpiopins.o leds.o serial.o

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	$(MAKE) stm32f4libs
	$(MAKE) otherlibs

lib: lib$(MCU).a

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
