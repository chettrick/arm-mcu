# Processor dependent make definitions

# $Id$

CPU		= arm7tdmi
CPUFLAGS	=
TEXTBASE	?= 0x00000000

AT91LIB		= $(MCUDIR)/at91lib

CFLAGS		+= -I$(AT91LIB)
LDFLAGS		+= -Wl,--section-start=startup=$(TEXTBASE)

LIBOBJS		= cpu.o leds.o serial.o

FLASHWRITEADDR	= 0x00100000

JLINKMCU	= at91sam7s512

# Board specific macro definitions

ifeq ($(BOARDNAME), OLIMEX_SAM7_P256)
MCU		= at91sam7s
endif

.PHONY:		default lib clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU)

default: lib$(MCU).a

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(AT91LIB)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(AT91LIB)/*.o
	$(MAKE) otherlibs

lib: lib$(MCU).a

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
