# Processor dependent make definitions

# $Id$

ARCH		= arm7tdmi

AT91LIB		= $(MCUDEPENDENT)/at91lib
USBSERIAL	= $(MCUDEPENDENT)/usb_serial
CFLAGS		+= -I$(AT91LIB) -I$(USBSERIAL)

LIBOBJS		= cpu.o device.o serial.o syscalls.o

.PHONY:		clean_$(MCU) lib reset

.SUFFIXES:	.flashocd

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(AT91LIB)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(AT91LIB)/*.o
	for F in $(USBSERIAL)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(USBSERIAL)/*.o

lib: lib$(MCU).a

# Reset the target

reset:
	$(MCUDEPENDENT)/reset.exp $(OPENOCD) $(OPENOCDCFG)

# Clean out working files

clean_$(MCU):
	rm -f *.a *.o $(AT91LIB)/*.o $(USBSERIAL)/*.o

# Define a suffix rule for programming the flash with OpenOCD

.bin.flashocd:
	$(MCUDEPENDENT)/flash.exp $(OPENOCD) $(OPENOCDCFG) $<
