# Processor dependent make definitions

# $Id$

CPU		= arm7tdmi
CPUFLAGS	=
MCU		= $(MCUFAMILY)
TEXTBASE	?= 0x00000000

CFLAGS		+= 
LDFLAGS		+= -Wl,--section-start=startup=$(TEXTBASE)

LPC21ISP	?= lpc21isp
LPC21ISPDEV	?= /dev/ttyS0
LPC21ISPBAUD	?= 115200
LPC21ISPCLOCK	?= 14746
LPC21ISPFLAGS	?= -control

# Board specific macro definitions

ifeq ($(BOARDNAME), MBED_LPC2368)
MBED		?= /media/MBED
endif

ifeq ($(BOARDNAME), OLIMEX_LPC_P2378)
JLINKMCU	= lpc2378
USBBOOT		?= /media/LPC23xx
endif

# Phony targets

.PHONY:		default lib clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU)
.SUFFIXES:	.flashisp .flashmbed .flashusb

default: lib

# Build processor dependent support library

LIBOBJS		= cpu.o leds.o serial.o

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	$(MAKE) otherlibs

lib: lib$(MCU).a

# Define a suffix rule for programming the flash with lpc21isp

.hex.flashisp:
	$(LPC21ISP) $(LPC21ISPFLAGS) $< $(LPC21ISPDEV) $(LPC21ISPBAUD) $(LPC21ISPCLOCK)

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
