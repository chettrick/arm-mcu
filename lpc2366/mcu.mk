# Processor dependent make definitions

# $Id$

CPU		= arm7tdmi

BOARDNAME	?= MBED_LPC2368

LIBOBJS		= cpu.o device.o serial.o syscalls.o

LPC21ISPDEV	?= /dev/ttyS0
LPC21ISPBAUD	?= 19200
LPC21ISPCLOCK	?= 12000
LPC21ISPFLAGS	?= -control

FLASHEXP	?= $(MCUDEPENDENT)/flash.exp
RESETEXP	?= $(MCUDEPENDENT)/reset.exp

MBED		?= /media/MBED

.PHONY:		clean_$(MCU) lib reset

.SUFFIXES:	.flashisp .flashocd .mbed

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)

lib: lib$(MCU).a

# Reset the target with OpenOCD

reset:
	$(RESETEXP) $(OPENOCD) $(OPENOCDCFG)

# Define a suffix rule for programming the flash with OpenOCD

.bin.flashocd:
	$(FLASHEXP) $(OPENOCD) $(OPENOCDCFG) $<

# Define a suffix rule for programming the flash with lpc21isp

.hex.flashisp:
	$(LPC21ISP) $(LPC21ISPFLAGS) $< $(LPC21ISPDEV) $(LPC21ISPBAUD) $(LPC21ISPCLOCK)

# Define a suffix rule for installing to an mbed board

.bin.mbed:
	test -d $(MBED) -a -w $(MBED)
	cp $< $(MBED)
	sync
	@echo -e "\nPress RESET on the LPC2368 mbed board to start $<\n"

# Clean out working files

clean_$(MCU):
	rm -f *.a *.o

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
