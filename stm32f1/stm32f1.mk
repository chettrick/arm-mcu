# STM32F1 family make definitions

# $Id$

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

CPUFLAGS	+= -mcpu=cortex-m3 -mthumb -DCORTEX_M3
FLASHWRITEADDR	?= 0x08000000
TEXTBASE	?= 0x00000000

CFLAGS		+= -DSTM32F10X
LDFLAGS		+= -Ttext $(TEXTBASE)

OPENOCDFLASH	= $(MCUDIR)/stm32f1.flashocd

# Board specific macro definitions

ifeq ($(BOARDNAME), OLIMEX_STM32_P103)
BOARDFLAGS	+= -DCONSOLE_PORT='"com2:115200,n,8,1"'
MCU		= stm32f103rb
endif

ifeq ($(BOARDNAME), OLIMEX_STM32_P107)
BOARDFLAGS	+= -DCONSOLE_PORT='"com3:115200,n,8,1"'
MCU		= stm32f107rb
endif

ifeq ($(BOARDNAME), STM32_VALUE_LINE_DISCOVERY)
BOARDFLAGS	+= -DCONSOLE_PORT='"com1:115200,n,8,1"'
IOFLAGS		+= -DCONSOLE_CONIO
MCU		= stm32f100rb
JLINKGDBIF	= -if SWD

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
STLINKCLIIF	= -c SWD
endif

ifeq ($(shell uname), Linux)
STLINKIF	= $(STLINKV1IF)
STLINKGDBIF	= $(STLINKV1GDBIF)
endif
endif

ifeq ($(BOARDNAME), W5200E01_M3)
BOARDFLAGS	+= -DCONSOLE_PORT='"com1:115200,n,8,1"'
MCU		= stm32f103c8
JLINKGDBIF	= -if SWD

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
STLINKCLIIF	= -c SWD
endif
endif

# Include MCU specific make file

include $(MCUDIR)/$(MCU).mk

include $(MCUDIR)/libs/stm32f1libs.mk

# Phony targets

.PHONY:		clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU)

# Build processor dependent support library

LIBOBJS		= cpu.o gpiopins.o leds.o serial.o spi.o

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	$(MAKE) stm32f1libs
	$(MAKE) otherlibs

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
