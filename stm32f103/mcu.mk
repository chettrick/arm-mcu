# Processor dependent make definitions

# $Id$

CPU		= cortex-m3
CPUFLAGS	= -mthumb

BOARDNAME	?= OLIMEX_STM32_P103

FWLIB		= $(MCUDEPENDENT)/FWLib
CFLAGS		+= -I$(FWLIB)

LIBOBJS		= cpu.o device.o serial.o syscalls.o

FLASHEXP	?= $(MCUDEPENDENT)/flash.exp
RESETEXP	?= $(MCUDEPENDENT)/reset.exp

.PHONY:		clean_$(MCU) lib reset

.SUFFIXES:	.flashocd

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(FWLIB)/*.S ; do $(MAKE) $${F%.S}.o ; done
	for F in $(FWLIB)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(FWLIB)/*.o

lib: lib$(MCU).a

# Reset the target with OpenOCD

reset:
	$(RESETEXP) $(OPENOCD) $(OPENOCDCFG)

# Define a suffix rule for programming the flash with OpenOCD

.bin.flashocd:
	$(FLASHEXP) $(OPENOCD) $(OPENOCDCFG) $<

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
