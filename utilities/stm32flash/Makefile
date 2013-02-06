# Makefile for stm32flash flash programming utility

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

STM32FLASH_NAME		= stm32flash
STM32FLASH_SERVER	= http://stm32flash.googlecode.com/files
STM32FLASH_DIST		= $(STM32FLASH_NAME).tar.gz
STM32FLASH_URL		= $(STM32FLASH_SERVER)/$(STM32FLASH_DIST)
STM32FLASH_DIR		= $(STM32FLASH_NAME).src
STM32FLASH_PROG		= $(STM32FLASH_NAME)

INSTALLDIR		= /usr/local/bin

TAR			= tar

.PHONY: default install clean reallyclean distclean

default: $(STM32FLASH_PROG)

# Download stm32flash source distribution

$(STM32FLASH_DIST):
	wget -O $(STM32FLASH_DIST) $(STM32FLASH_URL)

# Unpack stm32flash source distribution

$(STM32FLASH_DIR): $(STM32FLASH_DIST)
	$(TAR) xzf $(STM32FLASH_DIST)
	mv $(STM32FLASH_NAME) $(STM32FLASH_DIR)
	cd $(STM32FLASH_DIR) ; patch -b -p0 <../cygwin.patch

# Compile stm32flash

$(STM32FLASH_PROG): $(STM32FLASH_DIR)
	$(MAKE) -C $(STM32FLASH_DIR)
	cp $(STM32FLASH_DIR)/$(STM32FLASH_PROG) $(STM32FLASH_PROG)

# Install stm32flash

install: $(STM32FLASH_PROG)
	install -csm 0555 $(STM32FLASH_PROG) $(INSTALLDIR)

# Uninstall stm32flash

uninstall:
	-rm $(INSTALLDIR)/$(STM32FLASH_PROG)

# Clean out working files

clean:
	-rm $(STM32FLASH_PROG)

reallyclean: clean
	-rm -rf $(STM32FLASH_DIR)

distclean: reallyclean
	-rm $(STM32FLASH_DIST)
