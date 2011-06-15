# Processor dependent make definitions

# $Id$

CPU		= cortex-m3
CPUFLAGS	= -mthumb
TEXTBASE	?= 0x00000000

CMSIS		= $(MCUDIR)/CMSIS
FREERTOS	= $(MCUDIR)/FreeRTOS

CFLAGS		+= -I$(CMSIS)/include -I$(FREERTOS)
LDFLAGS		+= -Ttext $(TEXTBASE)

LIBOBJS		= cpu.o device.o gpiopins.o leds.o serial.o syscalls.o

.PHONY:		clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU) lib

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	for F in $(CMSIS)/source/*.c $(FREERTOS)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(CMSIS)/source/*.o
	$(AR) crs lib$(MCU).a $(FREERTOS)/*.o

lib: lib$(MCU).a

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
