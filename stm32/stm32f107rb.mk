# Processor dependent make definitions

# $Id$

CPU		= cortex-m3
CPUFLAGS	= -mthumb
TEXTBASE	?= 0x00000000

CMSIS		= $(MCUDIR)/CMSIS

CFLAGS		+= -DSTM32F10X_CL -DUSE_STDPERIPH_DRIVER -I$(CMSIS)/include
LDFLAGS		+= -Ttext $(TEXTBASE)

ifeq ($(WITH_FREERTOS), yes)
FREERTOS	= $(MCUDIR)/FreeRTOS
CFLAGS		+= -DFREERTOS -I$(FREERTOS)
endif

LIBOBJS		= cpu.o device.o gpiopins.o leds.o serial.o syscalls.o

JLINKADDR	= 0x08000000

.PHONY:		clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU) lib

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(CMSIS)/source/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(CMSIS)/source/*.o
ifeq ($(WITH_FREERTOS), yes)
	for F in $(FREERTOS)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(FREERTOS)/*.o
endif

lib: lib$(MCU).a

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
