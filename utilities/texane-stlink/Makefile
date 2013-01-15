# Makefile for building GDB server and flash utility for STM32 ST-Link

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

STLINKURL	= http://github.com/texane/stlink.git
STLINKSRC	= stlink
STLINKGDB	= stlink-gdbserver
STLINKFLASH	= stlink-flash

LIBUSBCFLAGS	?= -DLIBUSB_CALL='' $(shell pkg-config --cflags libusb-1.0)

INSTALLDIR	?= /usr/local/bin

default: $(STLINKGDB)

# Download stlink-gdbserver source distribution

$(STLINKSRC):
	git clone --depth 1 $(STLINKURL) $(STLINKSRC)
	cd $(STLINKSRC) && ./autogen.sh && ./configure USB_CFLAGS="$(LIBUSBCFLAGS)"

# Compile stlink-gdbserver

$(STLINKGDB): $(STLINKSRC)
	$(MAKE) -C $(STLINKSRC)
	cp $(STLINKSRC)/st-util				$(STLINKGDB)
	cp $(STLINKSRC)/st-flash			$(STLINKFLASH)

# Install stlink-gdbserver

install:
	install -csm 0555 $(STLINKGDB)			$(INSTALLDIR)
	install -csm 0555 $(STLINKFLASH)		$(INSTALLDIR)

# Uninstall stlink-gdbserver

uninstall:
	-rm $(INSTALLDIR)/$(STLINKGDB)
	-rm $(INSTALLDIR)/$(STLINKFLASH)

# Clean out working files

clean:
	-rm $(STLINKGDB)
	-rm $(STLINKFLASH)
	-$(MAKE) -C $(STLINKSRC) clean

reallyclean: clean

distclean: reallyclean
	-rm -rf $(STLINKSRC)
