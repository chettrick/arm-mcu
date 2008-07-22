# Processor dependent make definitions

# $Id: mcu.mk,v 1.2 2008-07-22 16:46:18 cvs Exp $

ARCH		= cortex-m3
THUMBFLAGS	= -mthumb

FWLIB		= $(MCUDEPENDENT)/FWLib
CFLAGS		+= -I$(FWLIB)

LIBOBJS		= conio.o cpu.o syscalls.o

.SUFFIXES:	.flashocd

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(FWLIB)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(FWLIB)/*.o

# Clean out working files

clean_$(MCU):
	rm -f *.a *.o $(FWLIB)/*.o

# Define a suffix rule for programming the flash with OpenOCD

.bin.flashocd:
	$(MCUDEPENDENT)/flash.exp $(OPENOCD) $(OPENOCDCFG) $<
