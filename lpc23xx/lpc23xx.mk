# Processor dependent make definitions

# $Id$

CPU		= arm7tdmi
CPUFLAGS	=
TEXTBASE	?= 0x00000000

BOARDNAME	?= MBED_LPC2368

CFLAGS		+= 
LDFLAGS		+= -Wl,--section-start=startup=$(TEXTBASE)

LIBOBJS		= cpu.o device.o serial.o syscalls.o

LPC21ISPDEV	?= /dev/ttyS0
LPC21ISPBAUD	?= 115200
LPC21ISPCLOCK	?= 14746
LPC21ISPFLAGS	?= -control

FLASHEXP	?= $(MCUDEPENDENT)/flash.exp
RESETEXP	?= $(MCUDEPENDENT)/reset.exp

MBED		?= /media/MBED
USBBOOT		?= /media/LPC23xx

.PHONY:		clean_$(MCU) lib reset

.SUFFIXES:	.flashisp .flashocd .flashmbed .flashusb

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)

lib: lib$(MCU).a

# Reset the target with OpenOCD

reset:
	$(RESETEXP) $(OPENOCD) $(OPENOCDCFG)

# Define a suffix rule for programming the flash with lpc21isp

.hex.flashisp:
	$(LPC21ISP) $(LPC21ISPFLAGS) $< $(LPC21ISPDEV) $(LPC21ISPBAUD) $(LPC21ISPCLOCK)

# Define a suffix rule for programming the flash with OpenOCD

.bin.flashocd:
	$(FLASHEXP) $(OPENOCD) $(OPENOCDCFG) $<

# Define a suffix rule for installing to an mbed board

.bin.flashmbed:
	test -d $(MBED) -a -w $(MBED)
	cp $< $(MBED)
	sync
	@echo -e "\nPress RESET on the mbed LPC2368 board to start $<\n"

# Define a suffix rule for installing via the NXP USB boot loader

.bin.flashusb:
	test -d $(USBBOOT) -a -w $(USBBOOT)
	cp $< $(USBBOOT)/firmware.bin
	sync
	@echo -e "\nPress RESET on the target board to start $<\n"

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
