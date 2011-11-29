# Make definitions for ST-Link

# $Id$

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
STLINKCLI	?= ST-LINK_CLI.exe
STLINKIF	?= -c JTAG
endif

ifeq ($(shell uname), Linux)
STLINKV1FLASH	?= stlink-v1-flash
STLINKV1IF	?= /dev/stlink-v1
STLINKV1GDBIF	?= --stlinkv1 --device=$(STLINKV1IF)

STLINKV2FLASH	?= stlink-flash
endif

STLINKDEBUG	?= $(ARMSRC)/common/main.gdb
STLINKGDB	?= stlink-gdbserver
STLINKGDBOPTS	?= -p $(GDBSERVERPORT)

.PHONY: startstlink stopstlink
.SUFFIXES: .debugstlink .flashstlink .flashstlinkv1

# Debug with ST-Link GDB server

.elf.debugstlink:
	$(MAKE) startstlink
	$(GDBGUI) $(GDB) $(GDBFLAGS) -x $(STLINKDEBUG) $<
	$(MAKE) stopstlink

# Program flash with ST-Link/V2

.bin.flashstlink:
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	$(STLINKCLI) $(STLINKIF) -ME -P $< $(FLASHWRITEADDR) -Rst
else
	$(STLINKV2FLASH) write $< $(FLASHWRITEADDR)
endif

# Program flash with legacy ST-Link/V1

.bin.flashstlinkv1:
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	$(STLINKCLI) $(STLINKIF) -ME -P $< $(FLASHWRITEADDR) -Rst
else
	$(STLINKV1FLASH) $(STLINKV1IF) program=$< reset run
endif

# Start ST-Link GDB server

startstlink:
	$(STLINKGDB) $(STLINKGDBIF) $(STLINKGDBOPTS) >debug.log 2>&1 &
	tcpwait localhost $(GDBSERVERPORT) 10

# Stop ST-Link GDB server

stopstlink:
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	killall `basename $(STLINKGDB) .exe`
else
	killall $(STLINKGDB)
endif
