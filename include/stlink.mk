# Make definitions for ST-Link

# $Id$

# Copyright (C)2013, Philip Munts, President, Munts AM Corp.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification,are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
#
# * Neither the name of Munts AM Corp. nor the names of its contributors may
#   be used to endorse or promote products derived from this software without
#   specific prior written permission.
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
STLINKCLI	?= ST-LINK_CLI.exe
STLINKCLIIF	?= -c JTAG
endif

ifeq ($(shell uname), Linux)
STLINKV1FLASH	?= stlink-v1-flash
STLINKV1IF	?= /dev/stlink-v1
STLINKV1GDBIF   ?= --stlinkv1 --device=$(STLINKV1IF)
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
	-skill `basename $(STLINKGDB) .exe`

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
	$(STLINKV2FLASH) write $(STLINKIF) $< $(FLASHWRITEADDR)
endif

# Program flash with legacy ST-Link/V1

.bin.flashstlinkv1:
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	$(STLINKCLI) $(STLINKCLIIF) -ME -P $< $(FLASHWRITEADDR) -Rst
else
	$(STLINKV1FLASH) $(STLINKV1IF) program=$< reset run
endif
