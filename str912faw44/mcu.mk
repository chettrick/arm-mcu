# Processor dependent make definitions

# $Id$

CPU		= arm9

BOARDNAME	?= STMICRO_STR910_EVAL

FWLIB		= $(MCUDEPENDENT)/FWLib
USBSERIAL	= $(MCUDEPENDENT)/usb_serial
CFLAGS		+= -I$(FWLIB) -I$(USBSERIAL)

LIBOBJS		= cpu.o device.o serial.o syscalls.o time.o

FLASHEXP	?= $(MCUDEPENDENT)/flash.exp
RESETEXP	?= $(MCUDEPENDENT)/reset.exp

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

# Reset the target with OpenOCD

reset:
	$(RESETEXP) $(OPENOCD) $(OPENOCDCFG)

# Define a suffix rule for programming the flash with OpenOCD

.bin.flashocd:
	$(FLASHEXP) $(OPENOCD) $(OPENOCDCFG) $<

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
