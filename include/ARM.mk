# Generic Makefile for compiling ARM microcontroller firmware

# $Id: ARM.mk,v 1.5 2007-10-29 15:51:08 cvs Exp $

ARMTOOLS	?= /usr/local/arm-tools
CC		= $(ARMTOOLS)/bin/arm-elf-gcc
LD		= $(ARMTOOLS)/bin/arm-elf-ld
AR		= $(ARMTOOLS)/bin/arm-elf-ar
STRIP		= $(ARMTOOLS)/bin/arm-elf-strip
OBJCOPY		= $(ARMTOOLS)/bin/arm-elf-objcopy
OBJDUMP		= $(ARMTOOLS)/bin/arm-elf-objdump
GDB		= $(ARMTOOLS)/bin/arm-elf-gdb
OPENOCD		= $(ARMTOOLS)/bin/openocd-ftd2xx

ARCH		?= arm7tdmi
MCU		?= lpc2119

ARMSRC		?= .
MCUDEPENDENT	?= $(ARMSRC)/$(MCU)
STARTUP		?= $(MCUDEPENDENT)/crt0.o
LINKERSCRIPT	?= $(MCUDEPENDENT)/linker.ld

CFLAGS		= -g -O -Wall -I$(ARMSRC) -I$(ARMSRC)/include -mcpu=$(ARCH) -DMCU_$(MCU) $(EXTRAFLAGS) $(DEBUG)
LDFLAGS		= -nostartfiles -T$(LINKERSCRIPT) -L$(MCUDEPENDENT) -l$(MCU)

# Define default target placeholder

default:
	@echo You must explicitly specify the target

# These targets are not files

.PHONY: default update clean startocd stopocd

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
	$(OPENOCD) -f `cygpath -a -w $(MCUDEPENDENT)/debug.ocd` &
else
	$(OPENOCD) -f $(MCUDEPENDENT)/debug.ocd &
endif

# Stop OpenOCD debug server

stopocd:
	killall $(OPENOCD)

# Update from CVS repository

update:
	p4update.sh

# Clean out working files

clean:
	rm -f *.asm *.bin *.elf *.hex *.o *.a flashocd.script $(MCUDEPENDENT)/*.o $(MCUDEPENDENT)/*.a

# Include flash programming support

include $(MCUDEPENDENT)/flash.mk
