# Processor dependent make definitions

# $Id$

# Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
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

CPUFLAGS	+= -mcpu=cortex-m0 -mthumb -DCORTEX_M0
FLASHWRITEADDR	?= 0x00000000
TEXTBASE	?= 0x00000000

CFLAGS		+= -DLPC11XX
LDFLAGS		+= -Ttext $(TEXTBASE)

# Board specific macro definitions

ifeq ($(BOARDNAME), PROTOBOARD_LPC1114FN28)
CONSOLEFLAGS	= -DCONSOLE_SERIAL -DCONSOLE_PORT='"com1:115200,n,8,1"'
IOFLAGS		= -DCONIO_STDIO
MCU		= LPC1114FN28
JLINKMCU	= LPC1114/102
JLINKGDBIF	= -if SWD
endif

ifeq ($(BOARDNAME), RASPBERRYPI_LPC1114)
CONSOLEFLAGS	= -DCONSOLE_SERIAL -DCONSOLE_PORT='"com1:115200,n,8,1"'
IOFLAGS		= -DCONIO_STDIO
MCU		= LPC1114FN28
JLINKMCU	= LPC1114/102
JLINKGDBIF	= -if SWD
endif

# Phony targets

.PHONY:		clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU)

# Build processor dependent support library

include $(MCUDIR)/CMSIS/CMSIS.mk

LIBOBJS		= $(MCU).o adc.o cpu.o gpio.o leds.o pwm.o serial.o timer.o spi.o $(EXTRALIBOBJS)

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	$(MAKE) $(LIBTARGETS)

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
