# Makefile for building and installing stlink-v1-flash

# $Id$

# Copyright (C)2013, Philip Munts, President, Munts AM Corp.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
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

HOSTCC		?= gcc
CFLAGS		?= -Wall

PROGRAM		= stlink-v1-flash
INSTALLDIR	?= /usr/local/bin

default: $(PROGRAM)

# Compile stlink-v1-flash

stlink-v1-flash: stlink-v1-flash.c
	$(HOSTCC) $(CFLAGS) -o $@ $<

# Install stlink-v1-flash

install: $(PROGRAM)
	install -csm 0555 $(PROGRAM)		$(INSTALLDIR)

# Uninstall stlink-v1-flash

uninstall:
	rm $(INSTALLDIR)/$(PROGRAM)

# Clean out working files

clean:
	-rm $(PROGRAM)

reallyclean: clean

distclean: reallyclean
