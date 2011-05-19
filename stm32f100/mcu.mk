# Processor dependent make definitions

# $Id$

CPU		= cortex-m3
CPUFLAGS	= -mthumb

BOARDNAME	?= STM32_VALUE_LINE_DISCOVERY

CMSIS		= $(MCUDEPENDENT)/CMSIS
CFLAGS		+= -DSTM32F10X_LD_VL -DUSE_STDPERIPH_DRIVER -I$(CMSIS)/include

LIBOBJS		= cpu.o device.o serial.o syscalls.o

STLINK		= stlink
STLINKDEV	= /dev/stlink

.PHONY:		clean_$(MCU) lib reset

.SUFFIXES:	.flashstlink

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(CMSIS)/source/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(CMSIS)/source/*.o

lib: lib$(MCU).a

# Define a suffix rule for programming the flash with stlink

.bin.flashstlink:
	$(STLINK) $(STLINKDEV) erase=all flash:w:$<

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
