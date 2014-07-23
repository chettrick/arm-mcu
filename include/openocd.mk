# Make definitions for OpenOCD

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

OPENOCD		?= openocd
OPENOCDCFG	?= $(MCUDIR)/$(MCU).openocd
OPENOCDDEBUG	?= $(ARMSRC)/common/main.gdb
OPENOCDFLASH	?= $(MCUDIR)/$(MCU).flashocd
OPENOCDIF	?= jtagkey2p

.PHONY: startocd stopocd
.SUFFIXES: .bin .debugocd .elf .flashocd

# Start OpenOCD

startocd:
	$(OPENOCD) -f interface/$(OPENOCDIF).cfg -f $(OPENOCDCFG) >debug.log 2>&1 &

# Stop OpenOCD

stopocd:
	-skill `basename $(OPENOCD) .exe`

# Debug with OpenOCD

.elf.debugocd:
	$(MAKE) startocd
	$(GDBGUI) $(GDB) $(GDBFLAGS) -x $(OPENOCDDEBUG) $<
	$(MAKE) stopocd

# Program flash with OpenOCD

.bin.flashocd:
	$(MAKE) startocd
	$(OPENOCDFLASH) $< $(FLASHWRITEADDR) $(TEXTBASE)
	$(MAKE) stopocd
