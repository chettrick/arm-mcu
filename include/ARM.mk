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

FLASHWRITEADDR	= 0x00000000

GDBSERVERPORT	= 3333

JLINKEXE	?= JLinkExe
JLINKFLASHCMDS	= jlinkflash.tmp
JLINKMCU	= $(MCU)
JLINKDEBUG	?= $(MCUDIR)/$(MCU).debugjlink
JLINKGDB	?= JLinkGDBServer
JLINKGDBIF	?= -if JTAG
JLINKGDBOPTS	?= -port $(GDBSERVERPORT)

LPC21ISP	?= lpc21isp
LPC21ISPDEV	?= /dev/ttyS0
LPC21ISPBAUD	?= 115200
LPC21ISPCLOCK	?= 14746
LPC21ISPFLAGS	?= -control

MBED		?= /media/MBED

OPENOCD		?= openocd
OPENOCDCFG	?= $(MCUDIR)/$(MCU).openocd
OPENOCDDEBUG	?= $(ARMSRC)/common/main.gdb
OPENOCDFLASH	?= $(MCUDIR)/$(MCU).flashocd
OPENOCDIF	?= olimex-jtag-tiny

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
STLINKCLI	?= ST-LINK_CLI.exe
endif
STLINKCLIIF	?= -c JTAG
STLINKGDB	?= stlink-gdbserver
STLINKDEBUG	?= $(ARMSRC)/common/main.gdb
STLINKGDBIF	?=
STLINKGDBOPTS	?= -p $(GDBSERVERPORT)

STM32FLASH	?= stm32flash
STM32FLASH_PORT	?= /dev/ttyS0

USBBOOT		?= /media/LPC17xx

MCUDIR		?= $(ARMSRC)/$(MCUFAMILY)
STARTUP		?= $(MCUDIR)/$(MCU).o
LINKERSCRIPT	?= $(MCUDIR)/$(MCU).ld

CPUFLAGS	?=
CONFIGFLAGS	?=
DEBUGFLAGS	?= -g
OPTFLAGS	?= -O0
IOFLAGS		?= -DINTEGER_STDIO
CFLAGS		+= -Wall -mcpu=$(CPU) $(CPUFLAGS) -D$(MCU) -D$(BOARDNAME) -ffunction-sections
CFLAGS		+= -I$(ARMSRC)/include -I$(MCUDIR)
CFLAGS		+= $(CONFIGFLAGS) $(DEBUGFLAGS) $(OPTFLAGS) $(IOFLAGS) $(DEBUG) $(EXTRAFLAGS)
LDFLAGS		+= -nostartfiles -T$(LINKERSCRIPT) -L$(MCUDIR) -l$(MCU) -Wl,-Map=$*.map,--cref,--entry=_start,--gc-sections $(EXTRAOBJS)

#GDBGUI		?= ddd --gdb --debugger
#GDBFLAGS	?= -tui

# Define default target placeholder

default_catch:
	@echo ERROR: You must explicitly specify a make target!
	@exit 1

# These targets are not files

.PHONY: default_catch update clean startjlink stopjlink startocd stopocd startstlink stopstlink

# These are the target suffixes

.SUFFIXES: .asm .c .bin .debugjlink .debugocd .debugstlink .elf .flashisp .flashjlink .flashmbed .flashocd .flashstlink .hex .o .s .S .stm32flash

# Don't delete intermediate files

.SECONDARY:

# Now define some suffix rules

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.o.elf:
	cd $(MCUDIR) && $(MAKE) $(MCU).o lib$(MCU).a
	$(CC) $(CFLAGS) -o $@ $(STARTUP) $< $(LDFLAGS)

.elf.asm:
	$(OBJDUMP) -S -d $< >$@

.elf.bin:
	$(OBJCOPY) -S -O binary --gap-fill=0 $< $@

.elf.debugjlink:
	$(MAKE) startjlink
	$(GDBGUI) $(GDB) $(GDBFLAGS) -x $(JLINKDEBUG) $<
	$(MAKE) stopjlink

.elf.debugocd:
	$(MAKE) startocd
	$(GDBGUI) $(GDB) $(GDBFLAGS) -x $(OPENOCDDEBUG) $<
	$(MAKE) stopocd

.elf.debugstlink:
	$(MAKE) startstlink
	$(GDBGUI) $(GDB) $(GDBFLAGS) -x $(STLINKDEBUG) $<
	$(MAKE) stopstlink

.elf.hex:
	$(OBJCOPY) -S -O ihex --gap-fill=0 $< $@

.s.o:
	$(CC) $(CFLAGS) -c -o $@ -c $<

.S.o:
	$(CC) $(CFLAGS) -c -o $@ -c $<

# Define a suffix rule for programming the flash with lpc21isp

.hex.flashisp:
	$(LPC21ISP) $(LPC21ISPFLAGS) $< $(LPC21ISPDEV) $(LPC21ISPBAUD) $(LPC21ISPCLOCK)

# Define a suffix rule for programming the flash with J-Link Commander

.bin.flashjlink:
	@echo "exec device=$(JLINKMCU)"			>$(JLINKFLASHCMDS)
	@echo "h"					>>$(JLINKFLASHCMDS)
	@echo "loadbin $<, 0x`dc -e '16o 16i $(subst 0x,,$(FLASHWRITEADDR)) $(subst 0x,,$(TEXTBASE)) + p'`"	>>$(JLINKFLASHCMDS)
	@echo "r"					>>$(JLINKFLASHCMDS)
	@echo "g"					>>$(JLINKFLASHCMDS)
	@echo "exit"					>>$(JLINKFLASHCMDS)
	-$(JLINKEXE) $(JLINKFLASHCMDS)
	@rm $(JLINKFLASHCMDS)
	@rm Default.ini

# Define a suffix rule for installing to an mbed board

.bin.flashmbed:
	test -d $(MBED) -a -w $(MBED)
	cp $< $(MBED)
	sync
	@echo -e "\nPress RESET on the target board to start $<\n"

# Define a suffix rule for programming the flash with OpenOCD

.bin.flashocd:
	$(MAKE) startocd
	$(OPENOCDFLASH) $< $(FLASHWRITEADDR) $(TEXTBASE)

# Define a suffix rule for programming the flash with stlink

.bin.flashstlink:
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	$(STLINKCLI) $(STLINKCLIIF) -ME -P $< $(FLASHWRITEADDR) -Rst
else
	$(STLINKFLASH) $(STLINKDEV) program=$< reset run
endif

# Define a suffix rule for installing via the NXP USB boot loader

.bin.flashusb:
	test -d $(USBBOOT) -a -w $(USBBOOT)
	cp $< $(USBBOOT)/firmware.bin
	sync
	@echo -e "\nPress RESET on the target board to start $<\n"

# Define a suffix rule for programming the flash with STM32 serial boot loader and stm32flash

.bin.stm32flash:
	$(STM32FLASH) -w $< -v -g 0x0 $(STM32FLASH_PORT)

# Start and stop J-Link GDB server

startjlink:
	$(JLINKGDB) $(JLINKGDBIF) $(JLINKGDBOPTS) >debug.log 2>&1 &
	tcpwait localhost $(GDBSERVERPORT) 10

stopjlink:
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	killall `basename $(JLINKGDB) .exe`
else
	killall $(JLINKGDB)
endif

# Start and stop OpenOCD

startocd:
	$(OPENOCD) -f interface/$(OPENOCDIF).cfg -f $(OPENOCDCFG) >debug.log 2>&1 &
	tcpwait localhost $(GDBSERVERPORT) 10

stopocd:
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	killall `basename $(OPENOCD) .exe`
else
	killall $(OPENOCD)
endif

# Start and stop ST-Link GDB server

startstlink:
	$(STLINKGDB) $(STLINKGDBIF) $(STLINKGDBOPTS) >debug.log 2>&1 &
	tcpwait localhost $(GDBSERVERPORT) 10

stopstlink:
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	killall `basename $(STLINKGDB) .exe`
else
	killall $(STLINKGDB)
endif

# Update from source code repository

update:
	svn status --no-ignore
	svn update

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

clean:
	cd $(MCUDIR) && $(MAKE) clean_$(MCU)
	find * -name '*.o' -exec rm {} ";"
	rm -f *.a *.asm *.bin *.elf *.hex *.log *.map *.stackdump *.tmp Default.ini
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

reallyclean: clean
	cd $(MCUDIR) && $(MAKE) reallyclean_$(MCU)

distclean: reallyclean
	cd $(MCUDIR) && $(MAKE) distclean_$(MCU)

# Include MCU dependent makefile

include $(MCUDIR)/$(MCUFAMILY).mk
