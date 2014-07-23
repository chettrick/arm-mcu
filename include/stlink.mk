# Make definitions for ST-Link

# $Id$

# Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
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

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
STLINKFLASH	?= ST-LINK_CLI.exe
STLINKIF	?= -c SWD
endif

ifeq ($(shell uname), Linux)
STLINKFLASH	?= stlink-flash
endif

ifeq ($(shell uname), OpenBSD)
STLINKFLASH	?= stlink-flash
endif

STLINKDEBUG	?= $(ARMSRC)/common/main.gdb
STLINKGDB	?= stlink-gdbserver
STLINKGDBOPTS	?= -p $(GDBSERVERPORT)

.SUFFIXES: .bin .debugstlink .elf .flashstlink .hex

# Start ST-Link GDB server

startstlink:
	$(STLINKGDB) $(STLINKGDBIF) $(STLINKGDBOPTS) >debug.log 2>&1 &

# Stop ST-Link GDB server

stopstlink:
	-skill `basename $(STLINKGDB) .exe`

# Debug with ST-Link GDB server

.elf.debugstlink:
	$(MAKE) startstlink
	$(GDBGUI) $(GDB) $(GDBFLAGS) -x $(STLINKDEBUG) $<
	$(MAKE) stopstlink

# Program flash with ST-Link

.bin.flashstlink:
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	"$(STLINKFLASH)" $(STLINKIF) -ME -P $< $(FLASHWRITEADDR) -Rst
else
	$(STLINKFLASH) --reset write $(STLINKIF) $< $(FLASHWRITEADDR)
endif

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
.hex.flashstlink:
	"$(STLINKFLASH)" $(STLINKIF) -ME -P $< -V -RST
endif
