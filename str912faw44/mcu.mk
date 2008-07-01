# Processor dependent make definitions

# $Id: mcu.mk,v 1.3 2008-07-01 19:21:11 cvs Exp $

ARCH		= arm9

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