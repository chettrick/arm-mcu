# Processor dependent make definitions

# $Id: mcu.mk,v 1.1 2008-07-01 19:07:24 cvs Exp $

ARCH		= arm7tdmi

LIBOBJS		= conio.o cpu.o syscalls.o

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)

# Clean out working files

clean_$(MCU):
	rm -f *.a *.o

# Define a suffix rule for programming the flash with OpenOCD

.SUFFIXES: .flashocd

# Program flash with OpenOCD

.bin.flashocd:
	$(MCUDEPENDENT)/flash.exp $(OPENOCD) $(OPENOCDCFG) $<
