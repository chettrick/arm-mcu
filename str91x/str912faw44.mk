# Processor dependent make definitions

# $Id$

CPU		= arm9
CPUFLAGS	=
TEXTBASE	?= 0x00000000

FWLIB		= $(MCUDIR)/FWLib
USBSERIAL	= $(MCUDIR)/usb_serial

CFLAGS		+= -I$(FWLIB) -I$(USBSERIAL)
LDFLAGS		+= -Wl,--section-start=startup=$(TEXTBASE)

LIBOBJS		= cpu.o device.o serial.o syscalls.o time.o

.PHONY:		clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU) lib

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(FWLIB)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(FWLIB)/*.o
	for F in $(USBSERIAL)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(USBSERIAL)/*.o

lib: lib$(MCU).a

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
