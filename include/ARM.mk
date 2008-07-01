# Generic Makefile for compiling ARM microcontroller firmware

# $Id: ARM.mk,v 1.39 2008-07-01 18:12:36 cvs Exp $

ARMTOOLS	?= /usr/local/arm-tools
GCCARCH		?= arm-elf
CC		= $(ARMTOOLS)/bin/$(GCCARCH)-gcc
LD		= $(ARMTOOLS)/bin/$(GCCARCH)-ld
AR		= $(ARMTOOLS)/bin/$(GCCARCH)-ar
STRIP		= $(ARMTOOLS)/bin/$(GCCARCH)-strip
OBJCOPY		= $(ARMTOOLS)/bin/$(GCCARCH)-objcopy
OBJDUMP		= $(ARMTOOLS)/bin/$(GCCARCH)-objdump
GDB		= $(ARMTOOLS)/bin/$(GCCARCH)-gdb
OPENOCD		= $(ARMTOOLS)/bin/openocd

ARMSRC		?= .
MCUDEPENDENT	?= $(ARMSRC)/$(MCU)
STARTUP		?= $(MCUDEPENDENT)/crt0.o
LINKERSCRIPT	?= $(MCUDEPENDENT)/linker.ld
OPENOCDCFG	?= $(MCUDEPENDENT)/openocd.cfg
DEBUGGDB	?= $(MCUDEPENDENT)/debug.gdb

GDBFLAGS	?= -g
OPTFLAGS	?= -O0
CFLAGS		+= -Wall -mcpu=$(ARCH) -DMCU_$(MCU)
CFLAGS		+= -I$(ARMSRC) -I$(ARMSRC)/include
CFLAGS		+= $(GDBFLAGS) $(OPTFLAGS) $(DEBUG) $(EXTRAFLAGS)
LDFLAGS		+= -nostartfiles -T$(LINKERSCRIPT) -L$(MCUDEPENDENT) -l$(MCU) -Wl,-Map=$*.map,--cref $(EXTRAOBJS)

# Define default target placeholder

default_catch:
	@echo ERROR: You must explicitly specify the target!
	@exit 1

# These targets are not files

.PHONY: default_catch update clean

# These are the target suffixes

.SUFFIXES: .asm .bin .debug .elf .hex .o

# Don't delete intermediate files

.SECONDARY:

# Now define some suffix rules

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.o.elf:
	cd $(MCUDEPENDENT) && $(MAKE) crt0.o lib$(MCU).a
	$(CC) $(CFLAGS) -o $@ $(STARTUP) $< $(LDFLAGS)

.elf.asm:
	$(OBJDUMP) -S -d $< >$@

.elf.bin:
	$(OBJCOPY) -S -O binary --gap-fill=0 $< $@

.elf.debug:
	$(OPENOCD) -f $(OPENOCDCFG) &
	sleep 1
	-$(GDB) -x $(DEBUGGDB) -w $<
	killall openocd

.elf.hex:
	$(OBJCOPY) -S -O ihex --gap-fill=0 $< $@

.s.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.S.o:
	$(CC) $(CFLAGS) -o $@ -c $<

# OpenOCD targets

startocd:
	$(OPENOCD) -f $(OPENOCDCFG) &

stopocd:
	killall openocd

# Update from CVS repository

update:
	cvs -q update

# Clean out working files

clean:
	cd $(MCUDEPENDENT) && $(MAKE) clean_$(MCU)
	rm -f *.a *.asm *.bin *.elf *.hex *.map *.o

# Include flash programming support

include $(MCUDEPENDENT)/flash.mk
