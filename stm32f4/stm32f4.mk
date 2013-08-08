# STM32F4 family make definitions

# $Id: stm32.mk 3236 2011-11-03 11:31:27Z svn $

# Copyright (C)2013, Philip Munts, President, Munts AM Corp.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

CPUFLAGS	+= -mcpu=cortex-m4 -mthumb -DCORTEX_M4
FLASHWRITEADDR	?= 0x08000000
TEXTBASE	?= 0x00000000

CFLAGS		+= -DSTM32F4XX
LDFLAGS		+= -Ttext $(TEXTBASE)

JLINKGDBIF	= -if SWD

OPENOCDCFG	= $(MCUDIR)/stm32f4.openocd
OPENOCDFLASH	= $(MCUDIR)/stm32f4.flashocd
OPENOCDIF	= stlink-v2

ifeq ($(WITH_FPU), yes)
CPUFLAGS	+= -mfloat-abi=hard -mfpu=fpv4-sp-d16
RMAKEFLAGS	+= WITH_FPU=$(WITH_FPU)
endif

# Board specific macro definitions

ifeq ($(BOARDNAME), STM32F4_DISCOVERY)
MCU		= stm32f407vg
BOARDFLAGS	+= -DHSE_VALUE=8000000
CONSOLEFLAGS	?= -DCONSOLE_USB
#CONSOLEFLAGS	?= -DCONSOLE_SERIAL -DCONSOLE_PORT='"com2:115200,n,8,1"'
endif

ifeq ($(BOARDNAME), FEZ_CERB40)
MCU		= stm32f405rg
BOARDFLAGS	+= -DHSE_VALUE=12000000
CONSOLEFLAGS	?= -DCONSOLE_USB
#CONSOLEFLAGS	?= -DCONSOLE_SERIAL -DCONSOLE_PORT='"com2:115200,n,8,1"'
endif

ifeq ($(BOARDNAME), NETDUINO2)
MCU		= stm32f405rg
BOARDFLAGS	+= -DHSE_VALUE=25000000
CONSOLEFLAGS	?= -DCONSOLE_USB
#CONSOLEFLAGS	?= -DCONSOLE_SERIAL -DCONSOLE_PORT='"com2:115200,n,8,1"'
endif

# USB serial port support

USBSERIAL	= $(MCUDIR)/usb_serial
CFLAGS		+= -I$(USBSERIAL)

# Phony targets

.PHONY:		clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU) lib

# Build processor dependent support library

include $(MCUDIR)/libs/stm32f4libs.mk

LIBOBJS		= $(MCU).o cpu.o gpiopins.o leds.o serial.o $(EXTRALIBOBJS)

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(USBSERIAL)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(USBSERIAL)/*.o
	$(MAKE) $(LIBTARGETS)

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
