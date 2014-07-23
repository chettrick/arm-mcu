# Make definitions for J-Link

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

JLINKEXE	?= JLinkExe
JLINKFLASHCMDS	= jlinkflash.tmp
JLINKMCU	= $(MCU)
JLINKDEBUG	?= $(MCUDIR)/$(MCU).debugjlink
JLINKGDB	?= JLinkGDBServer
JLINKGDBIF	?= -if JTAG
JLINKGDBOPTS	?= -port $(GDBSERVERPORT)

.PHONY: startjlink stopjlink
.SUFFIXES: .bin .debugjlink .elf .flashjlink

# Start J-Link GDB server

startjlink:
	$(JLINKGDB) $(JLINKGDBIF) $(JLINKGDBOPTS) >debug.log 2>&1 &

# Stop J-Link GDB server

stopjlink:
	-skill `basename $(JLINKGDB) .exe`

# Debug with J-Link

.elf.debugjlink:
	$(MAKE) startjlink
	$(GDBGUI) $(GDB) $(GDBFLAGS) -x $(JLINKDEBUG) $<
	$(MAKE) stopjlink

# Flash with J-Link

.bin.flashjlink:
	@echo "device $(JLINKMCU)"			>$(JLINKFLASHCMDS)
ifneq ($(JLINKSPEED),)
	@echo "speed $(JLINKSPEED)"			>>$(JLINKFLASHCMDS)
endif
	@echo "h"					>>$(JLINKFLASHCMDS)
	@echo "loadbin $<, 0x`dc -e '16o 16i $(subst 0x,,$(FLASHWRITEADDR)) $(subst 0x,,$(TEXTBASE)) + p'`"	>>$(JLINKFLASHCMDS)
	@echo "r"					>>$(JLINKFLASHCMDS)
	@echo "g"					>>$(JLINKFLASHCMDS)
	@echo "exit"					>>$(JLINKFLASHCMDS)
	-$(JLINKEXE) $(JLINKFLASHCMDS)
	@rm $(JLINKFLASHCMDS)
	@if [ -f Default.ini ]; then rm Default.ini ; fi
