# Processor dependent make definitions

# $Id$

CPU		= cortex-m3
CPUFLAGS	= -mthumb
MCU		= $(MCUFAMILY)
TEXTBASE	?= 0x00000000

CMSIS		= $(MCUDIR)/CMSIS

CFLAGS		+= -DLPC17XX -I$(CMSIS)/include
LDFLAGS		+= -Ttext $(TEXTBASE)

LPC21ISP	?= lpc21isp
LPC21ISPDEV	?= /dev/ttyS0
LPC21ISPBAUD	?= 115200
LPC21ISPCLOCK	?= 14746
LPC21ISPFLAGS	?= -control

# Board specific macro definitions

ifeq ($(BOARDNAME), MBED_LPC1768)
MBED		?= /media/MBED
endif

ifeq ($(BOARDNAME), BLUEBOARD_LPC1768_H)
JLINKMCU	= lpc1768
USBBOOT		?= /media/LPC17xx
endif

# Phony targets

.PHONY:		default lib clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU)
.SUFFIXES:	.flashisp .flashmbed .flashusb

default: lib

# Build processor dependent support library

LIBOBJS		= cpu.o gpiopins.o leds.o serial.o

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(CMSIS)/source/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(CMSIS)/source/*.o
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
	@echo -e "\nPress RESET on the mbed LPC1768 board to start $<\n"

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
