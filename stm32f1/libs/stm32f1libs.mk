# Makefile for STM32F1 libraries imported from ST and other sources

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

LIBSDIR		= $(ARMSRC)/stm32f1/libs
CMSIS		= $(LIBSDIR)/CMSIS
DRIVERS		= $(LIBSDIR)/drivers

CFLAGS		+= -I$(CMSIS)/CM3/CoreSupport -I$(CMSIS)/CM3/DeviceSupport/ST/STM32F10x
CFLAGS		+= -DUSE_STDPERIPH_DRIVER -I$(DRIVERS)/inc

stm32f1libs:
	$(MAKE) $(CMSIS)/CM3/CoreSupport/core_cm3.o
	$(MAKE) $(CMSIS)/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.o
	for F in $(DRIVERS)/src/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(FIND) $(LIBSDIR) -type f -name '*.o' -exec $(AR) crs lib$(MCU).a {} ";"
