# Generic Makefile for compiling ARM microcontroller firmware

# $Id: ARM.mk,v 1.13 2007-12-12 07:41:11 cvs Exp $

ARMTOOLS	?= /usr/local/arm-tools
CC		= $(ARMTOOLS)/bin/arm-elf-gcc
LD		= $(ARMTOOLS)/bin/arm-elf-ld
AR		= $(ARMTOOLS)/bin/arm-elf-ar
STRIP		= $(ARMTOOLS)/bin/arm-elf-strip
OBJCOPY		= $(ARMTOOLS)/bin/arm-elf-objcopy
OBJDUMP		= $(ARMTOOLS)/bin/arm-elf-objdump
GDB		= $(ARMTOOLS)/bin/arm-elf-gdb
OPENOCD		= $(ARMTOOLS)/bin/openocd-ftd2xx

ARMSRC		?= .
MCUDEPENDENT	?= $(ARMSRC)/$(MCU)
STARTUP		?= $(MCUDEPENDENT)/crt0.o
LINKERSCRIPT	?= $(MCUDEPENDENT)/linker.ld

GDBFLAGS	?= -g
OPTFLAGS	?= -O
CFLAGS		= -Wall -I$(ARMSRC) -I$(ARMSRC)/include -mcpu=$(ARCH) -DMCU_$(MCU) $(GDBFLAGS) $(OPTFLAGS) $(EXTRAFLAGS) $(DEBUG)
LDFLAGS		= -nostartfiles -T$(LINKERSCRIPT) -L$(MCUDEPENDENT) -l$(MCU)

# Define default target placeholder

default_catch:
	@echo ERROR: You must explicitly specify the target!
	@exit 1

# These targets are not files

.PHONY: default_catch update clean startocd stopocd resetocd

# These are the target suffixes

.SUFFIXES: .asm .bin .debug .elf .hex .o

# Don't delete intermediate files

.SECONDARY:

# Now define some suffix rules

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.o.elf:
	cd $(MCUDEPENDENT) ; $(MAKE) lib$(MCU).a
	$(CC) $(CFLAGS) -o $@ $(STARTUP) $< $(LDFLAGS) $(EXTRAOBJS)

.elf.asm:
	$(OBJDUMP) -S -d $< >$@

.elf.bin:
	$(OBJCOPY) -S -O binary --gap-fill=0 $< $@

.elf.debug:
	$(MAKE) startocd
	$(GDB) -x $(MCUDEPENDENT)/debug.gdb -w $<
	$(MAKE) stopocd

.elf.hex:
	$(OBJCOPY) -S -O ihex --gap-fill=0 $< $@

.S.o:
	$(CC) $(CFLAGS) -o $@ -c $<

# Start OpenOCD debug server

startocd:
ifeq ($(OS), Windows_NT)
	$(OPENOCD) -f "`cygpath -a -w $(MCUDEPENDENT)/debug.ocd`" &
else
	$(OPENOCD) -f $(MCUDEPENDENT)/debug.ocd &
endif

# Stop OpenOCD debug server

stopocd:
	killall $(OPENOCD)

# Reset target using OpenOCD

resetocd:
	echo "reset run" >reset.script
	echo "shutdown" >> reset.script
	$(OPENOCD) -f "`cygpath -a -w $(MCUDEPENDENT)/reset.ocd`"

# Update from CVS repository

update:
	cvs -q update

# Clean out working files

clean:
	rm -f *.asm *.bin *.elf *.hex *.o *.a *.script $(MCUDEPENDENT)/*.o $(MCUDEPENDENT)/*.a

# Include flash programming support

include $(MCUDEPENDENT)/flash.mk
