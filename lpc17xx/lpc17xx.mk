# Processor dependent make definitions

# $Id$

MCU		= $(MCUFAMILY)

CPUFLAGS	+= -mcpu=cortex-m3 -mthumb -DCORTEX_M3
FLASHWRITEADDR	?= 0x00000000
TEXTBASE	?= 0x00000000

CFLAGS		+= -DLPC17XX
LDFLAGS		+= -Ttext $(TEXTBASE)

# Board specific macro definitions

ifeq ($(BOARDNAME), MBED_LPC1768)
BOARDFLAGS	?= -DDEFAULT_CPU_FREQ=100000000 -DCONSOLE_PORT="com1:115200,n,8,1"
endif

ifeq ($(BOARDNAME), BLUEBOARD_LPC1768_H)
BOARDFLAGS	?= -DDEFAULT_CPU_FREQ=100000000 -DCONSOLE_PORT="com1:115200,n,8,1"
JLINKMCU	= lpc1768
JLINKGDBIF	= -if SWD
endif

# Phony targets

.PHONY:		lib clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU)

# Build processor dependent support library

include $(MCUDIR)/libs/lpc17xxlibs.mk

LIBOBJS		= cpu.o gpiopins.o leds.o serial.o

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	$(MAKE) lpc17xxlibs
	$(MAKE) otherlibs

lib: lib$(MCU).a

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
