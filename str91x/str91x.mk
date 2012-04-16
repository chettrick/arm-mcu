# Processor dependent make definitions

# $Id$

CPUFLAGS	+= -mcpu=arm9 -marm
FLASHWRITEADDR	?= 0x00000000
TEXTBASE	?= 0x00000000

FWLIB		= $(MCUDIR)/FWLib
USBSERIAL	= $(MCUDIR)/usb_serial

CFLAGS		+= -I$(FWLIB) -I$(USBSERIAL)
LDFLAGS		+= -Wl,--section-start=startup=$(TEXTBASE)

# Board specific macro definitions

ifeq ($(BOARDNAME), STMICRO_STR910_EVAL)
MCU		= str912faw44
endif

# Phony targets

.PHONY:		lib clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU)

# Build processor dependent support library

LIBOBJS		= cpu.o leds.o serial.o time.o

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(FWLIB)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(FWLIB)/*.o
	for F in $(USBSERIAL)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(USBSERIAL)/*.o
	$(MAKE) otherlibs

lib: lib$(MCU).a

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
