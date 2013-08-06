# Makefile for building OpenOCD for Linux

# Get prebuilt Windows binaries from:
# http://www.freddiechopin.info/index.php/en/download/category/4-openocd

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

OPENOCD_NAME	= openocd
OPENOCD_VER	= 0.7.0
OPENOCD_SRC	= $(OPENOCD_NAME)-$(OPENOCD_VER)
OPENOCD_TARBALL	= $(OPENOCD_SRC).tar.gz
OPENOCD_DIST	= $(TEMP)/$(OPENOCD_TARBALL)
OPENOCD_SERVER	= http://sourceforge.net/projects/openocd/files/openocd/$(OPENOCD_VER)
OPENOCD_URL	= $(OPENOCD_SERVER)/$(OPENOCD_TARBALL)

default: compile.done

# Download OpenOCD source distribution

$(OPENOCD_DIST):
	wget -P $(TEMP) $(OPENOCD_URL)

# Unpack OpenOCD source distribution

source.done: $(OPENOCD_DIST)
	tar xzf $(OPENOCD_DIST)
	touch $@

# Compile OpenOCD

compile.done: source.done
	cd $(OPENOCD_SRC) ; ./configure --prefix=/usr/local --enable-ft2232_libftdi	\
	--enable-usb_blaster_libftdi --enable-presto_libftdi --enable-usbprog		\
	--enable-jlink --enable-vsllink --enable-rlink --enable-ulink			\
	--enable-arm-jtag-ew --enable-buspirate --enable-stlink --enable-opendous	\
	$(EXTRACONFIG)
	$(MAKE) -C $(OPENOCD_SRC)
	$(MAKE) -C $(OPENOCD_SRC) docs
	touch $@

# Install OpenOCD

install:
	$(MAKE) -C $(OPENOCD_SRC) install install-pdf

# Create OpenOCD RPM package

fakeroot: compile.done
	$(MAKE) -C $(OPENOCD_SRC) install install-pdf DESTDIR=`pwd`/fakeroot
	find fakeroot -name dir -exec rm {} ";"
	find fakeroot -type f -exec chmod ugo-w {} ";"

specfile: fakeroot specfile.template
	sed s/@@VERSION@@/$(OPENOCD_VER)/g <specfile.template >specfile
	find fakeroot/usr/local/openocd-$(OPENOCD_VER) -type d | awk '{ printf("%%dir /%s\n", substr($$1, 10)); }' >>specfile
	find fakeroot -type f | cut -c 9- >>specfile
	find fakeroot -type l | cut -c 9- >>specfile

rpm: specfile
	rpmbuild --buildroot=`pwd`/fakeroot --define="_topdir `pwd`/rpmbuild" -bb specfile
	cp rpmbuild/RPMS/*/*.rpm .

# Clean out working files

clean:
	-$(MAKE) -C $(OPENOCD_SRC) clean
	-rm compile.done
	-rm *.rpm
	-rm specfile
	-rm -rf fakeroot rpmbuild

reallyclean: clean
	-rm -rf $(OPENOCD_SRC)
	-rm source.done

distclean: reallyclean
	-rm $(OPENOCD_DIST)
