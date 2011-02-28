# Processor dependent make definitions

# $Id$

TEMP		?= /tmp

CPU		= cortex-m3
CPUFLAGS	= -mthumb

BOARDNAME	?= MBED_LPC1768

CMSIS_DIR	= $(MCUDEPENDENT)/CMSIS

CFLAGS		+= -I$(CMSIS_DIR)/include

LIBOBJS		= cpu.o device.o serial.o syscalls.o

MBED		?= /media/MBED

.PHONY:		clean_$(MCU) lib reset

.SUFFIXES:	.flashisp .flashocd .mbed

# Build processor dependent support library

lib$(MCU).a: $(CMSIS_DIR) $(LIBOBJS)
	for F in $(CMSIS_DIR)/source/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(LIBOBJS) 
	$(AR) crs lib$(MCU).a $(CMSIS_DIR)/source/*.o

lib: lib$(MCU).a

# Define a suffix rule for installing to an mbed board

.bin.mbed:
	test -d $(MBED) -a -w $(MBED)
	cp $< $(MBED)
	sync
	@echo -e "\nPress RESET on the LPC1768 mbed board to start $<\n"

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
