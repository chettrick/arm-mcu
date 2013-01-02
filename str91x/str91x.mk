# Processor dependent make definitions

# $Id$

CPUFLAGS	+= -mcpu=arm9
FLASHWRITEADDR	?= 0x00000000
TEXTBASE	?= 0x00000000

FWLIB		= $(MCUDIR)/FWLib

CFLAGS		+= -I$(FWLIB)
LDFLAGS		+= -Wl,--section-start=startup=$(TEXTBASE)

ifeq ($(WITH_USBSERIAL), yes)
USBSERIAL	= $(MCUDIR)/usb_serial
CFLAGS		+= -I$(USBSERIAL)
IOFLAGS		+= -DCONSOLE_USB
endif

# Board specific macro definitions

ifeq ($(BOARDNAME), STMICRO_STR910_EVAL)
ifneq ($(WITH_USBSERIAL), yes)
BOARDFLAGS	+= -DCONSOLE_PORT='"com1:115200,n,8,1"'
endif
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
ifeq ($(WITH_USBSERIAL), yes)
	for F in $(USBSERIAL)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(USBSERIAL)/*.o
endif
	$(MAKE) otherlibs

lib: lib$(MCU).a

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
