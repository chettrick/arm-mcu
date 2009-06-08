# Processor dependent make definitions

# $Id$

ARCH		= arm7tdmi

LIBOBJS		= conio.o cpu.o syscalls.o

.PHONY:		reset

.SUFFIXES:	.flashocd

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)

# Reset the target

reset:
	$(MCUDEPENDENT)/reset.exp $(OPENOCD) $(OPENOCDCFG)

# Clean out working files

clean_$(MCU):
	rm -f *.a *.o

# Define a suffix rule for programming the flash with OpenOCD

.bin.flashocd:
	$(MCUDEPENDENT)/flash.exp $(OPENOCD) $(OPENOCDCFG) $<
