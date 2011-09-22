# STM32 family make definitions

# $Id$

CPU		= cortex-m3
CPUFLAGS	= -mthumb
TEXTBASE	?= 0x00000000

CMSIS		= $(MCUDIR)/CMSIS

CFLAGS		+= -DSTM32F10X -DUSE_STDPERIPH_DRIVER -I$(CMSIS)/include
LDFLAGS		+= -Ttext $(TEXTBASE)

LIBOBJS		= cpu.o device.o gpiopins.o leds.o serial.o spi.o syscalls.o

JLINKADDR	= 0x08000000

STM32FLASH	?= stm32flash
STM32FLASH_PORT	?= /dev/ttyS0

ifeq ($(shell uname), Linux)
STLINKEXE	?= stlink
STLINKDEV	?= /dev/stlink
endif

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
STLINKEXE	?= ST-LINK_CLI.exe
endif

.PHONY:		clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU) lib

.SUFFIXES:	.flashstlink .stm32flash

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(CMSIS)/source/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(CMSIS)/source/*.o
	$(MAKE) otherlibs

lib: lib$(MCU).a

# Define a suffix rule for programming the flash with stlink

ifeq ($(shell uname), Linux)
.bin.flashstlink:
	$(STLINKEXE) $(STLINKDEV) -v erase=all flash:w:$<
endif

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
.bin.flashstlink:
	$(STLINKEXE) -c SWD -ME -P $< 0x08000000 -Rst
endif

# Define a suffix rule for programming the flash with serial boot loader and stm32flash

.bin.stm32flash:
	$(STM32FLASH) -w $< -v -g 0x0 $(STM32FLASH_PORT)

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
