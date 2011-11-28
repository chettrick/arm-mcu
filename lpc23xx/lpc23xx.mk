# Processor dependent make definitions

# $Id$

CPU		= arm7tdmi
CPUFLAGS	=
MCU		= $(MCUFAMILY)
TEXTBASE	?= 0x00000000

CFLAGS		+= 
LDFLAGS		+= -Wl,--section-start=startup=$(TEXTBASE)

# Board specific macro definitions

ifeq ($(BOARDNAME), OLIMEX_LPC_P2378)
JLINKMCU	= lpc2378
endif

# Phony targets

.PHONY:		default lib clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU)

default: lib

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
