# Generic Makefile for compiling ARM microcontroller firmware

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

# Toolchain definitions

ARMTOOLS	?= /usr/local/arm-tools
CROSS_COMPILE	?= $(ARMTOOLS)/bin/arm-none-eabi-

CC		= $(CROSS_COMPILE)gcc
CXX		= $(CROSS_COMPILE)g++
LD		= $(CROSS_COMPILE)ld
AR		= $(CROSS_COMPILE)ar
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump
GDB		= $(CROSS_COMPILE)gdb

FIND		?= find

# Framework general definitions

MCUDIR		?= $(ARMSRC)/$(MCUFAMILY)
STARTUP		?= $(MCUDIR)/$(MCU).o
LINKERSCRIPT	?= $(MCUDIR)/$(MCU).ld

MCUFAMILYNAME	:= $(shell echo $(MCUFAMILY) | tr '[a-z]' '[A-Z]')

# Compiler and linker flags

CPUFLAGS	+= -D$(MCU) -D$(BOARDNAME) -DMCUFAMILYNAME='"$(MCUFAMILYNAME)"'
DEBUGFLAGS	?= -g
OPTFLAGS	?= -O0
ifeq ($(WITH_CONIO), yes)
IOFLAGS		+= -DCONSOLE_CONIO
else
IOFLAGS		+= -DINTEGER_STDIO
endif
CFLAGS		+= -Wall -ffunction-sections
CFLAGS		+= -I$(ARMSRC)/include -I$(MCUDIR)
CFLAGS		+= $(OPTFLAGS) $(CPUFLAGS) $(BOARDFLAGS) $(IOFLAGS) $(CONFIGFLAGS) $(DEBUGFLAGS) $(EXTRAFLAGS)
CXXFLAGS	+= -fpermissive -fno-exceptions -fno-rtti -fno-use-cxa-atexit
LDFLAGS		+= -nostartfiles -T$(LINKERSCRIPT) -L$(MCUDIR) -l$(MCU)
ifeq ($(WITH_LIBSTDCPP), yes)
LDFLAGS		+= -lstdc++
endif
LDFLAGS		+= -Wl,-Map=$*.map,--cref,--entry=_start,--gc-sections $(EXTRAOBJS)

# GDB definitions

GDBSERVERPORT	= 3333
#GDBGUI		?= ddd --gdb --debugger
#GDBFLAGS	?= -tui

# These targets are not files

.PHONY: ARM_mk_default ARM_mk_clean

# These are the target suffixes

.SUFFIXES: .asm .c .cpp .bin .dmp .elf .hex .o .s .S

# Don't delete intermediate files

.SECONDARY:

# Now define some suffix rules

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.cpp.o:
	$(CXX) $(CXXFLAGS) $(CFLAGS) -c -o $@ $<

.o.elf:
	cd $(MCUDIR) && $(MAKE) $(MCU).o lib$(MCU).a BOARDNAME=$(BOARDNAME)
	$(CC) $(CFLAGS) -o $@ $(STARTUP) $< $(LDFLAGS)

.elf.asm:
	$(OBJDUMP) -S -d $< >$@

.elf.bin:
	$(OBJCOPY) -S -O binary --gap-fill=0 $< $@

.elf.hex:
	$(OBJCOPY) -S -O ihex --gap-fill=0 $< $@

.bin.dmp:
	hexdump -C $< > $@

.s.o:
	$(CC) $(CFLAGS) -c -o $@ -c $<

.S.o:
	$(CC) $(CFLAGS) -c -o $@ -c $<

# Support for common library functions

COMMON_DIR	= $(ARMSRC)/common
include $(COMMON_DIR)/common.mk

# Support for FreeRTOS

ifeq ($(WITH_FREERTOS), yes)
FREERTOS_DIR	= $(ARMSRC)/FreeRTOS/Cortex-M3
include $(FREERTOS_DIR)/FreeRTOS.mk
endif

# Support for LWIP TCP/IP protocol stack

ifeq ($(WITH_LWIP), yes)
LWIP_DIR        = $(ARMSRC)/lwip
include $(LWIP_DIR)/LWIP.mk
endif

# Support for WizNet device drivers

ifeq ($(WITH_WIZNET), yes)
WIZNET_DIR      = $(ARMSRC)/wiznet
include $(WIZNET_DIR)/wiznet.mk
endif

# Define default target placeholder

ARM_mk_default:
	@echo ERROR: You must explicitly specify a make target!
	@exit 1

# Build other library components

otherlibs:
	$(MAKE) common_lib
ifeq ($(WITH_FREERTOS), yes)
	$(MAKE) freertos_lib
endif
ifeq ($(WITH_LWIP), yes)
	$(MAKE) lwip_lib
endif
ifeq ($(WITH_WIZNET), yes)
	$(MAKE) wiznet_lib
endif

# Clean out working files

ARM_mk_clean:
	$(FIND) * -name '*.o' -exec rm {} ";"
	rm -f *.a *.asm *.bin *.dmp *.elf *.hex *.log *.map *.stackdump *.tmp Default.ini
	cd $(MCUDIR) && $(MAKE) clean_$(MCU)
	cd $(MCUDIR) && $(FIND) * -name '*.o' -exec rm {} ";"
	cd $(MCUDIR) && rm -f *.a *.asm *.bin *.dmp *.elf *.hex *.log *.map *.stackdump *.tmp Default.ini
	$(MAKE) common_clean
ifeq ($(WITH_FREERTOS), yes)
	$(MAKE) freertos_clean
endif
ifeq ($(WITH_LWIP), yes)
	$(MAKE) lwip_clean
endif
ifeq ($(WITH_WIZNET), yes)
	$(MAKE) wiznet_clean
endif

# Include programming and debugging makefiles

include $(ARMSRC)/include/jlink.mk
include $(ARMSRC)/include/lpc21isp.mk
include $(ARMSRC)/include/mbed.mk
include $(ARMSRC)/include/nxpusb.mk
include $(ARMSRC)/include/openocd.mk
include $(ARMSRC)/include/pg4uw.mk
include $(ARMSRC)/include/stlink.mk
include $(ARMSRC)/include/stm32flash.mk

# Include MCU dependent makefile

include $(MCUDIR)/$(MCUFAMILY).mk

# Include optional subordinate makefiles

sinclude $(HOME)/src/include/subversion.mk
