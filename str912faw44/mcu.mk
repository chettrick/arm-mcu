# Processor dependent make definitions

# $Id: mcu.mk,v 1.4 2008-07-02 17:42:17 cvs Exp $

ARCH		= arm9

FWLIB		= $(MCUDEPENDENT)/FWLib
CFLAGS		+= -I$(FWLIB)

USBSERIAL	= $(MCUDEPENDENT)/usb_serial

LIBOBJS		= conio.o cpu.o syscalls.o

.SUFFIXES:	.flashocd

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(FWLIB)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(FWLIB)/*.o
	for F in $(USBSERIAL)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs libusb_serial.a $(USBSERIAL)/*.o

# Clean out working files

clean_$(MCU):
	rm -f *.a *.o $(FWLIB)/*.o $(USBSERIAL)/*.o

# Define a suffix rule for programming the flash with OpenOCD

.bin.flashocd:
	$(MCUDEPENDENT)/flash.exp $(OPENOCD) $(OPENOCDCFG) $<
