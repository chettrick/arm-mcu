# Processor dependent make definitions

# $Id$

MCU		= $(MCUFAMILY)

CPUFLAGS	+= -mcpu=arm7tdmi -marm
FLASHWRITEADDR	?= 0x00000000
TEXTBASE	?= 0x00000000

CFLAGS		+= 
LDFLAGS		+= -Wl,--section-start=startup=$(TEXTBASE)

# Board specific macro definitions

ifeq ($(BOARDNAME), OLIMEX_LPC_P2378)
JLINKMCU	= lpc2378
endif

# Phony targets

.PHONY:		lib clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU)

# Build processor dependent support library

LIBOBJS		= cpu.o leds.o serial.o

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	$(MAKE) otherlibs

lib: lib$(MCU).a

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
