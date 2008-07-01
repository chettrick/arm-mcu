# Processor dependent make definitions

# $Id: mcu.mk,v 1.2 2008-07-01 19:20:11 cvs Exp $

ARCH		= arm7tdmi

LIBOBJS		= conio.o cpu.o syscalls.o

.SUFFIXES:	.flashocd

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)

# Clean out working files

clean_$(MCU):
	rm -f *.a *.o

# Define a suffix rule for programming the flash with OpenOCD

.bin.flashocd:
	$(MCUDEPENDENT)/flash.exp $(OPENOCD) $(OPENOCDCFG) $<
