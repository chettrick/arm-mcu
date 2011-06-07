# Processor dependent make definitions

# $Id$

CPU		= cortex-m3
CPUFLAGS	= -mthumb
TEXTBASE	?= 0x00000000

CMSIS		= $(MCUDIR)/CMSIS

CFLAGS		+= -DSTM32F10X_LD_VL -DUSE_STDPERIPH_DRIVER -I$(CMSIS)/include
LDFLAGS		+= -Ttext $(TEXTBASE)

LIBOBJS		= cpu.o device.o serial.o syscalls.o

ifeq ($(shell uname), Linux)
STLINK		= stlink
STLINKDEV	= /dev/stlink
endif

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
STLINK		= "/c/Program Files/STMicroelectronics/STM32 ST-LINK Utility/ST-LINK Utility"/ST-LINK_CLI.exe
endif

.PHONY:		clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU) lib

.SUFFIXES:	.flashstlink

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(CMSIS)/source/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(CMSIS)/source/*.o

lib: lib$(MCU).a

# Define a suffix rule for programming the flash with stlink

ifeq ($(shell uname), Linux)
.bin.flashstlink:
	$(STLINK) $(STLINKDEV) -v erase=all flash:w:$<
endif

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
.bin.flashstlink:
	$(STLINK) -c SWD -ME -P $< 0x08000000 -Rst
endif

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
