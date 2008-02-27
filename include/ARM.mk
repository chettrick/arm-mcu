# Generic Makefile for compiling ARM microcontroller firmware

# $Id: ARM.mk,v 1.26 2008-02-27 08:41:57 cvs Exp $

ARMTOOLS	?= /usr/local/arm-tools
CC		= $(ARMTOOLS)/bin/arm-elf-gcc
LD		= $(ARMTOOLS)/bin/arm-elf-ld
AR		= $(ARMTOOLS)/bin/arm-elf-ar
STRIP		= $(ARMTOOLS)/bin/arm-elf-strip
OBJCOPY		= $(ARMTOOLS)/bin/arm-elf-objcopy
OBJDUMP		= $(ARMTOOLS)/bin/arm-elf-objdump
GDB		= $(ARMTOOLS)/bin/arm-elf-gdb
OPENOCD		= $(ARMTOOLS)/bin/openocd

ARMSRC		?= .
MCUDEPENDENT	?= $(ARMSRC)/$(MCU)
STARTUP		?= $(MCUDEPENDENT)/crt0.o
LINKERSCRIPT	?= $(MCUDEPENDENT)/linker.ld
OPENOCDCFG	?= $(MCUDEPENDENT)/openocd.cfg
DEBUGGDB	?= $(MCUDEPENDENT)/debug.gdb

GDBFLAGS	?= -g
OPTFLAGS	?= -O
CFLAGS		+= -Wall -I$(ARMSRC) -I$(ARMSRC)/include -mcpu=$(ARCH) -DMCU_$(MCU) $(GDBFLAGS) $(OPTFLAGS) $(DEBUG) $(EXTRAFLAGS)
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
	cd $(MCUDEPENDENT) ; $(MAKE) crt0.o lib$(MCU).a
	$(CC) $(CFLAGS) -o $@ $(STARTUP) $< $(LDFLAGS)

.elf.asm:
	$(OBJDUMP) -S -d $< >$@

.elf.bin:
	$(OBJCOPY) -S -O binary --gap-fill=0 $< $@

.elf.debug:
	$(OPENOCD) -f $(OPENOCDCFG) &
	$(GDB) -x $(DEBUGGDB) -w $<
	killall openocd

.elf.hex:
	$(OBJCOPY) -S -O ihex --gap-fill=0 $< $@

.s.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.S.o:
	$(CC) $(CFLAGS) -o $@ -c $<

# Update from CVS repository

update:
	cvs -q update

# Clean out working files

clean:
	rm -f *.asm *.bin *.elf *.hex *.map *.o *.a *.script $(MCUDEPENDENT)/*.o $(MCUDEPENDENT)/*.a

# Include flash programming support

include $(MCUDEPENDENT)/flash.mk
