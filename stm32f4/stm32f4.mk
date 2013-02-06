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
# * Neither the name of Munts AM Corp. nor the names of its contributors may
#   be used to endorse or promote products derived from this software without
#   specific prior written permission.
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

OPENOCDFLASH	= $(MCUDIR)/stm32f4.flashocd

ifeq ($(WITH_FPU), yes)
CPUFLAGS	+= -mfloat-abi=hard -mfpu=fpv4-sp-d16
endif

# Board specific macro definitions

ifeq ($(BOARDNAME), STM32F4_DISCOVERY)
BOARDFLAGS	+= -DHSE_VALUE=8000000
WITH_USBSERIAL	?= yes

ifneq ($(WITH_USBSERIAL), yes)
BOARDFLAGS	+= -DCONSOLE_PORT='"com2:115200,n,8,1"'
endif
MCU		= stm32f407vg
JLINKGDBIF	= -if SWD

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
STLINKCLIIF	= -c SWD
endif
endif

ifeq ($(BOARDNAME), FEZ_CERB40)
BOARDFLAGS	+= -DHSE_VALUE=12000000
WITH_USBSERIAL	?= yes

ifneq ($(WITH_USBSERIAL), yes)
BOARDFLAGS	+= -DCONSOLE_PORT='"com2:115200,n,8,1"'
endif
MCU		= stm32f405rg
JLINKGDBIF	= -if SWD

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
STLINKCLIIF	= -c SWD
endif
endif

# USB serial port console support

ifeq ($(WITH_USBSERIAL), yes)
USBSERIAL	= $(MCUDIR)/usb_serial
CFLAGS		+= -I$(USBSERIAL)
IOFLAGS		+= -DCONSOLE_USB
endif

# Phony targets

.PHONY:		clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU) lib

# Build processor dependent support library

include $(MCUDIR)/libs/stm32f4libs.mk

LIBOBJS		= cpu.o gpiopins.o leds.o serial.o

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	$(MAKE) stm32f4libs
ifeq ($(WITH_USBSERIAL), yes)
	for F in $(USBSERIAL)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(USBSERIAL)/*.o
endif
	$(MAKE) otherlibs

lib: lib$(MCU).a

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
