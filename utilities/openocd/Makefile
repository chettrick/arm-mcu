# Makefile for building OpenOCD for Linux

# Get OpenOCD for windows from:
#  http://www.freddiechopin.info/index.php/en/download/category/4-openocd

# $Id$

OPENOCD_NAME	= openocd
OPENOCD_VER	= 0.5.0
OPENOCD_SRC	= $(OPENOCD_NAME)-$(OPENOCD_VER)
OPENOCD_TARBALL	= $(OPENOCD_SRC).tar.gz
OPENOCD_DIST	= $(TEMP)/$(OPENOCD_TARBALL)
OPENOCD_SERVER	= http://sourceforge.net/projects/openocd/files/openocd/$(OPENOCD_VER)
OPENOCD_URL	= $(OPENOCD_SERVER)/$(OPENOCD_TARBALL)
OPENOCD_RPM	= $(OPENOCD_NAME)-$(OPENOCD-VER).rpm

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
	cd $(OPENOCD_SRC) ; ./configure --enable-ft2232-libftdi --enable-jlink --enable-rlink --enable-ulink --enable-vsllink --enable-arm-jtag-ew --enable-buspirate
	$(MAKE) -C $(OPENOCD_SRC)
	touch $@

# Install OpenOCD

install: compile.done
	$(MAKE) -C $(OPENOCD_SRC) install

# Clean out working files

clean:
	$(MAKE) -C $(OPENOCD_SRC) clean
	-rm compile.done

reallyclean: clean
	-rm -rf $(OPENOCD_SRC)
	-rm source.done

distclean: reallyclean
	rm $(OPENOCD_DIST)
