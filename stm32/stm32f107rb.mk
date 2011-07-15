# Processor dependent make definitions

# $Id$

CPU		= cortex-m3
CPUFLAGS	= -mthumb
TEXTBASE	?= 0x00000000

CMSIS		= $(MCUDIR)/CMSIS

CFLAGS		+= -DSTM32F10X -DSTM32F10X_CL -DUSE_STDPERIPH_DRIVER -I$(CMSIS)/include
LDFLAGS		+= -Ttext $(TEXTBASE)

ifeq ($(WITH_FREERTOS), yes)
FREERTOS_DIR	= $(ARMSRC)/FreeRTOS/Cortex-M3
include $(FREERTOS_DIR)/FreeRTOS.mk
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
	$(MAKE) freertos_lib
endif

lib: lib$(MCU).a

# Clean out working files

clean_$(MCU):
ifeq ($(WITH_FREERTOS), yes)
	$(MAKE) freertos_clean
endif

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
