# Processor dependent make definitions

# $Id$

TEMP		?= /tmp

CPU		= cortex-m3
CPUFLAGS	= -mthumb
TEXTBASE	?= 0x00000000

BOARDNAME	?= MBED_LPC1768

CMSIS_DIR	= $(MCUDEPENDENT)/CMSIS

CFLAGS		+= -I$(CMSIS_DIR)/include
LDFLAGS		+= -Ttext $(TEXTBASE)

LIBOBJS		= cpu.o device.o serial.o syscalls.o

LPC21ISPDEV	?= /dev/ttyS0
LPC21ISPBAUD	?= 19200
LPC21ISPCLOCK	?= 14746
LPC21ISPFLAGS	?= -control

FLASHEXP	?= $(MCUDEPENDENT)/flash.exp
RESETEXP	?= $(MCUDEPENDENT)/reset.exp

MBED		?= /media/MBED
BLUEBOARD	?= /media/BLUEBOARD

.PHONY:		clean_$(MCU) lib reset

.SUFFIXES:	.flashisp .flashocd .mbed .blueboard

include $(ARMSRC)/lwip/LWIP.mk

# Build processor dependent support library

lib$(MCU).a: $(CMSIS_DIR) $(LIBOBJS) $(LWIP_OBJS)
	for F in $(CMSIS_DIR)/source/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(LIBOBJS) $(LWIP_OBJS)
	$(AR) crs lib$(MCU).a $(CMSIS_DIR)/source/*.o

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

.bin.mbed:
	test -d $(MBED) -a -w $(MBED)
	cp $< $(MBED)
	sync
	@echo -e "\nPress RESET on the LPC1768 mbed board to start $<\n"

# Define a suffix rule for installing to a BlueBoard

.bin.blueboard:
	test -d $(BLUEBOARD) -a -w $(BLUEBOARD)
	cat $< >$(BLUEBOARD)/firmware.bin
	sync
	umount /media/CRP*
	@echo -e "\nPress RESET on the BlueBoard LPC1768-H to start $<\n"

# Clean out working files

clean_$(MCU):
	cd $(LWIP_DIR) && find * -name '*.o' -exec rm {} ";"

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
