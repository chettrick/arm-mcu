# Make definitions for ST-Link

# $Id$

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
STLINKFLASH	?= ST-LINK_CLI.exe
STLINKIF	?= -c JTAG
endif
ifeq ($(shell uname), Linux)
STLINKFLASH	?= stlink-flash
STLINKIF	?=
endif
STLINKDEBUG	?= $(ARMSRC)/common/main.gdb
STLINKGDB	?= stlink-gdbserver
STLINKGDBOPTS	?= -p $(GDBSERVERPORT)

.PHONY: startstlink stopstlink
.SUFFIXES: .debugstlink .flashstlink

# Debug with ST-Link GDB server

.elf.debugstlink:
	$(MAKE) startstlink
	$(GDBGUI) $(GDB) $(GDBFLAGS) -x $(STLINKDEBUG) $<
	$(MAKE) stopstlink

# Program flash with ST-Link

.bin.flashstlink:
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	$(STLINKFLASH) $(STLINKIF) -ME -P $< $(FLASHWRITEADDR) -Rst
else
	$(STLINKFLASH) write $(STLINKIF) $< $(FLASHWRITEADDR)
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
