# Processor dependent make definitions

# $Id$

CPUFLAGS	+= -mcpu=arm7tdmi
FLASHWRITEADDR	?= 0x00100000
TEXTBASE	?= 0x00000000

AT91LIB		= $(MCUDIR)/at91lib

CFLAGS		+= -I$(AT91LIB)
LDFLAGS		+= -Wl,--section-start=startup=$(TEXTBASE)

# Board specific macro definitions

ifeq ($(BOARDNAME), OLIMEX_SAM7_P256)
BOARDFLAGS	?= -DCONSOLE_PORT='"com1:115200,n,8,1"'
MCU		= at91sam7s
JLINKMCU	= at91sam7s512
PG4UWPRJ	= at91sam7s256.eprj
endif

# Phony targets

.PHONY:		lib clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU)

# Build processor dependent support library

LIBOBJS		= cpu.o leds.o serial.o

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
