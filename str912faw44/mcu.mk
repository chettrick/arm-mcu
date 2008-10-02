# Processor dependent make definitions

# $Id: mcu.mk,v 1.7 2008-10-02 17:26:14 cvs Exp $

ARCH		= arm9

FWLIB		= $(MCUDEPENDENT)/FWLib
USBLIB		= $(MCUDEPENDENT)/usb_serial
CFLAGS		+= -I$(FWLIB) -I$(USBLIB)

USBSERIAL	= $(MCUDEPENDENT)/usb_serial

LIBOBJS		= cpu.o device.o serial.o syscalls.o

.PHONY:		reset

.SUFFIXES:	.flashocd

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(FWLIB)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(FWLIB)/*.o
	for F in $(USBSERIAL)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(USBSERIAL)/*.o

# Reset the target

reset:
	$(MCUDEPENDENT)/reset.exp $(OPENOCD) $(OPENOCDCFG)

# Clean out working files

clean_$(MCU):
	rm -f *.a *.o $(FWLIB)/*.o $(USBSERIAL)/*.o

# Define a suffix rule for programming the flash with OpenOCD

.bin.flashocd:
	$(MCUDEPENDENT)/flash.exp $(OPENOCD) $(OPENOCDCFG) $<
