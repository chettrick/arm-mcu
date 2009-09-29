# Processor dependent make definitions

# $Id$

ARCH		= arm9

FWLIB		= $(MCUDEPENDENT)/FWLib
USBSERIAL	= $(MCUDEPENDENT)/usb_serial
CFLAGS		+= -I$(FWLIB) -I$(USBSERIAL)

LIBOBJS		= cpu.o device.o serial.o syscalls.o time.o

.PHONY:		clean_$(MCU) lib reset

.SUFFIXES:	.flashocd

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(FWLIB)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(FWLIB)/*.o
	for F in $(USBSERIAL)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(USBSERIAL)/*.o

lib: lib$(MCU).a

# Reset the target

reset:
	$(MCUDEPENDENT)/reset.exp $(OPENOCD) $(OPENOCDCFG)

# Clean out working files

clean_$(MCU):
	rm -f *.a *.o $(FWLIB)/*.o $(USBSERIAL)/*.o

# Define a suffix rule for programming the flash with OpenOCD

.bin.flashocd:
	$(MCUDEPENDENT)/flash.exp $(OPENOCD) $(OPENOCDCFG) $<
