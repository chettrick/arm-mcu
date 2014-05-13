# Makefile for building a Mikropascal ARM application program

# $Id$

# Copyright (C)2014, Philip Munts, President, Munts AM Corp.
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

# Keep intermediate (especially .hex) files

.SECONDARY:

# Compiler definitions

MIKROPASCAL	?= "C:/Users/Public/Documents/Mikroelektronika/mikroPascal PRO for ARM/mPARM.exe"

# Pretty printer definitions

PTOP		?= ptop
PTOP_CFG	= $(ARMSRC)/mikropascal/ptop.cfg
PTOP_FLAGS	= -i -c $(PTOP_CFG)

# Define a pattern rule to build a Mikropascal ARM project

%.hex: %.mppar
	$(MIKROPASCAL) -RA -PF $<

# Define a pattern rule to format a Pascal source program using the the ptop
# utility from Free Pascal

%.prettyprint: %.mpas
	$(PTOP) $(PTOP_FLAGS) $< $<.tmp && mv $<.tmp $<

# Default target

mikropascal_mk_default:
	@echo ERROR: You must explicitly specify a make target!
	@exit 1

# Remove working files

mikropascal_mk_clean:
	-rm -f *.asm *.bin *.bmk *.brk *.dbg *.dct *.dlt *.emcl *.hex *.log *.lst *callertable.txt *.mpas.ini *.user.dic
