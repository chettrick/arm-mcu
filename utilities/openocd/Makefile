# Makefile for building OpenOCD for Linux

# Get prebuilt Windows binaries from:
# http://www.freddiechopin.info/index.php/en/download/category/4-openocd

# $Id$

OPENOCD_NAME	= openocd
OPENOCD_VER	= 0.5.0
OPENOCD_SRC	= $(OPENOCD_NAME)-$(OPENOCD_VER)
OPENOCD_TARBALL	= $(OPENOCD_SRC).tar.gz
OPENOCD_DIST	= $(TEMP)/$(OPENOCD_TARBALL)
OPENOCD_SERVER	= http://sourceforge.net/projects/openocd/files/openocd/$(OPENOCD_VER)
OPENOCD_URL	= $(OPENOCD_SERVER)/$(OPENOCD_TARBALL)
OPENOCD_RELEASE	:= $(shell pwd)/$(OPENOCD_NAME)-$(OPENOCD_VER)-$(shell uname -o)-$(shell uname -m).tgz

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
	cd $(OPENOCD_SRC) ; ./configure --prefix=/usr/local						\
	--enable-ft2232_libftdi --enable-gw16012 --disable-parport --disable-parport-ppdev		\
	--enable-presto_libftdi --enable-amtjtagaccel --enable-arm-jtag-ew				\
	--enable-jlink --enable-rlink --enable-usbprog --enable-vsllink --enable-usb_blaster_libftdi
	$(MAKE) -C $(OPENOCD_SRC)
	$(MAKE) -C $(OPENOCD_SRC) docs
	touch $@

# Install OpenOCD

install:
	$(MAKE) -C $(OPENOCD_SRC) install install-pdf install-html

# Clean out working files

clean:
	-$(MAKE) -C $(OPENOCD_SRC) clean
	-rm $(OPENOCD_RELEASE)
	-rm compile.done

reallyclean: clean
	-rm -rf $(OPENOCD_SRC)
	-rm source.done

distclean: reallyclean
	-rm $(OPENOCD_DIST)
