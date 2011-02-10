# Processor dependent make definitions

# $Id$

TEMP		?= /tmp

CPU		= cortex-m3
CPUFLAGS	= -mthumb

BOARDNAME	?= MBED_LPC1768

CMSIS_SERVER	= http://ics.nxp.com/support/documents/microcontrollers/zip
CMSIS_DIST	= $(TEMP)/lpc17xx.cmsis.driver.library.zip
CMSIS_URL	= $(CMSIS_SERVER)/$(CMSIS_DIST)
CMSIS_DIR	= $(MCUDEPENDENT)/LPC1700CMSIS

CFLAGS		+= -I$(CMSIS_DIR)/Core/CM3/CoreSupport
CFLAGS		+= -I$(CMSIS_DIR)/Core/CM3/DeviceSupport/NXP/LPC17xx
CFLAGS		+= -I$(CMSIS_DIR)/Drivers/include

LIBOBJS		= cpu.o device.o syscalls.o

MBED		?= /media/MBED

.PHONY:		clean_$(MCU) lib reset

.SUFFIXES:	.flashisp .flashocd .mbed

# Download CMSIS source distribution

$(CMSIS_DIST):
	wget -P $(TEMP) $(CMSIS_URL)

# Unpack CMSIS source distribution

$(CMSIS_DIR): $(CMSIS_DIST)
	unzip -q $(CMSIS_DIST) -x LPC1700CMSIS_ReleaseNotes.txt
	cd $(CMSIS_DIR) ; patch -p0 <../LPC1700CMSIS.patch
	touch $@

# Build processor dependent support library

lib$(MCU).a: $(CMSIS_DIR) $(LIBOBJS)
	for F in $(CMSIS_DIR)/Core/CM3/CoreSupport/*.c ; do $(MAKE) $${F%.c}.o ; done
	for F in $(CMSIS_DIR)/Core/CM3/DeviceSupport/NXP/LPC17xx/*.c ; do $(MAKE) $${F%.c}.o ; done
	for F in $(CMSIS_DIR)/Drivers/source/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(LIBOBJS) 
	$(AR) crs lib$(MCU).a $(CMSIS_DIR)/Core/CM3/CoreSupport/*.o
	$(AR) crs lib$(MCU).a $(CMSIS_DIR)/Core/CM3/DeviceSupport/NXP/LPC17xx/*.o
	$(AR) crs lib$(MCU).a $(CMSIS_DIR)/Drivers/source/*.o

lib: lib$(MCU).a

# Clean out working files

clean_$(MCU):
	-rm -f *.a *.o

reallyclean_$(MCU): clean_$(MCU)
	-rm -rf $(CMSIS_DIR)

distclean_$(MCU): reallyclean_$(MCU)
	-rm $(CMSIS_DIST)

# Define a suffix rule for installing to an mbed board

.bin.mbed:
	test -d $(MBED) -a -w $(MBED)
	cp $< $(MBED)
	sync
	@echo -e "\nPress RESET on the LPC1768 mbed board to start $<\n"
