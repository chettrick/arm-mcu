# Make definitions for ST-Link

# $Id$

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
STLINKCLI	?= ST-LINK_CLI.exe
STLINKCLIIF	?= -c JTAG
endif

ifeq ($(shell uname), Linux)
STLINKV1FLASH	?= stlink-v1-flash
STLINKV1IF	?= /dev/stlink-v1
STLINKV2FLASH	?= stlink-flash
endif

ifeq ($(shell uname), OpenBSD)
STLINKV2FLASH	?= stlink-flash
endif

STLINKDEBUG	?= $(ARMSRC)/common/main.gdb
STLINKGDB	?= stlink-gdbserver
STLINKGDBOPTS	?= -p $(GDBSERVERPORT)

.PHONY: startstlink stopstlink
.SUFFIXES: .debugstlink .flashstlink .flashstlinkv1

# Start ST-Link/V2 GDB server

startstlink:
	$(STLINKGDB) $(STLINKGDBIF) $(STLINKGDBOPTS) >debug.log 2>&1 &

# Stop ST-Link/V2 GDB server

stopstlink:
	skill `basename $(STLINKGDB) .exe`

# Debug with ST-Link/V2 GDB server

.elf.debugstlink:
	$(MAKE) startstlink
	$(GDBGUI) $(GDB) $(GDBFLAGS) -x $(STLINKDEBUG) $<
	$(MAKE) stopstlink

# Program flash with ST-Link/V2

.bin.flashstlink:
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	$(STLINKCLI) $(STLINKCLIIF) -ME -P $< $(FLASHWRITEADDR) -Rst
else
	$(STLINKV2FLASH) write $< $(FLASHWRITEADDR)
endif

# Program flash with legacy ST-Link/V1

.bin.flashstlinkv1:
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	$(STLINKCLI) $(STLINKCLIIF) -ME -P $< $(FLASHWRITEADDR) -Rst
else
	$(STLINKV1FLASH) $(STLINKV1IF) program=$< reset run
endif
