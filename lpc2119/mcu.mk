# Processor dependent make definitions

# $Id$

ARCH		= arm7tdmi-s

LIBOBJS		= conio.o cpu.o syscalls.o

LPC21ISPDEV	?= /dev/cua00
LPC21ISPBAUD	?= 19200
LPC21ISPCLOCK	?= 19660
LPC21ISPFLAGS	?= -control

.PHONY:		reset

.SUFFIXES:	.flashisp .flashocd

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)

# Reset the target

reset:
	$(MCUDEPENDENT)/reset.exp $(OPENOCD) $(OPENOCDCFG)

# Clean out working files

clean_$(MCU):
	rm -f *.a *.o

# Define a suffix rule for programming the flash with lpc21isp

.hex.flashisp:
	$(LPC21ISP) $(LPC21ISPFLAGS) $< $(LPC21ISPDEV) $(LPC21ISPBAUD) $(LPC21ISPCLOCK)

# Define a suffix rule for programming the flash with OpenOCD

.bin.flashocd:
	$(MCUDEPENDENT)/flash.exp $(OPENOCD) $(OPENOCDCFG) $<
