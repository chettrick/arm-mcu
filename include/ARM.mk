# Generic Makefile for compiling ARM microcontroller firmware

# $Id$

ARMTOOLS	?= /usr/local/arm-tools
CROSS_COMPILE	?= $(ARMTOOLS)/bin/arm-elf-

CC		= $(CROSS_COMPILE)gcc
LD		= $(CROSS_COMPILE)ld
AR		= $(CROSS_COMPILE)ar
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump
GDB		= $(CROSS_COMPILE)gdb

LPC21ISP	?= lpc21isp
OPENOCD		?= openocd

MCUDEPENDENT	?= $(ARMSRC)/$(MCU)
STARTUP		?= $(MCUDEPENDENT)/crt0.o
LINKERSCRIPT	?= $(MCUDEPENDENT)/linker.ld
OPENOCDCFG	?= $(MCUDEPENDENT)/openocd.cfg
DEBUGGDB	?= $(MCUDEPENDENT)/debug.gdb

ARCHFLAGS	?= -marm
CONFIGFLAGS	?=
GDBFLAGS	?= -g
OPTFLAGS	?= -O0
CFLAGS		+= -Wall -mcpu=$(ARCH) $(ARCHFLAGS) -DMCU_$(MCU)
CFLAGS		+= -I$(ARMSRC)/include -I$(MCUDEPENDENT)
CFLAGS		+= $(CONFIGFLAGS) $(GDBFLAGS) $(OPTFLAGS) $(DEBUG) $(EXTRAFLAGS)
LDFLAGS		+= -nostartfiles -T$(LINKERSCRIPT) -L$(MCUDEPENDENT) -l$(MCU) -Wl,-Map=$*.map,--cref $(EXTRAOBJS)

# Define default target placeholder

default_catch:
	@echo ERROR: You must explicitly specify a make target!
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
	-rm ~/.gdbtkinit
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

# Update from source code repository

update:
	svn status
	svn update

# Clean out working files

clean:
	cd $(MCUDEPENDENT) && $(MAKE) clean_$(MCU)
	rm -f *.a *.asm *.bin *.elf *.hex *.map *.o

# Include MCU dependent makefile

include $(MCUDEPENDENT)/mcu.mk
