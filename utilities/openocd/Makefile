# Makefile for building OpenOCD for Linux and Cygwin

# $Id$

LIBFTDI_NAME	= libftdi
LIBFTDI_VER	= 0.19
LIBFTDI_SRC	= $(LIBFTDI_NAME)-$(LIBFTDI_VER)
LIBFTDI_TARBALL	= $(LIBFTDI_SRC).tar.gz
LIBFTDI_DIST	= $(TEMP)/$(LIBFTDI_TARBALL)
LIBFTDI_SERVER	= http://www.intra2net.com/en/developer/libftdi/download
LIBFTDI_URL	= $(LIBFTDI_SERVER)/$(LIBFTDI_TARBALL)
LIBFTDI_DEST	:= $(shell pwd)/libftdi

OPENOCD_NAME	= openocd
OPENOCD_VER	= 0.5.0
OPENOCD_SRC	= $(OPENOCD_NAME)-$(OPENOCD_VER)
OPENOCD_TARBALL	= $(OPENOCD_SRC).tar.gz
OPENOCD_DIST	= $(TEMP)/$(OPENOCD_TARBALL)
OPENOCD_SERVER	= http://sourceforge.net/projects/openocd/files/openocd/$(OPENOCD_VER)
OPENOCD_URL	= $(OPENOCD_SERVER)/$(OPENOCD_TARBALL)
OPENOCD_RPM	= $(OPENOCD_NAME)-$(OPENOCD-VER).rpm
OPENOCD_DEST	:= $(shell pwd)/openocd

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
LIBFTDI_DIR	:= $(shell pwd)/libftdi
CFLAGS		+= -I$(LIBFTDI_DIR)/include
LDFLAGS		+= -L$(LIBFTDI_DIR)/lib
endif

default: compile.done

# Download libftdi source distribution

$(LIBFTDI_DIST):
	wget -P $(TEMP) $(LIBFTDI_URL)

# Build libftdi

$(LIBFTDI_DEST): $(LIBFTDI_DIST)
	rm -rf $(LIBFTDI_SRC)
	tar xzf $(LIBFTDI_DIST)
	cd $(LIBFTDI_SRC) ; ./configure --prefix=$(LIBFTDI_DEST)
	$(MAKE) -C $(LIBFTDI_SRC)
	$(MAKE) -C $(LIBFTDI_SRC) install
	touch $@

libftdi: $(LIBFTDI_DEST)

# Download OpenOCD source distribution

$(OPENOCD_DIST):
	wget -P $(TEMP) $(OPENOCD_URL)

# Unpack OpenOCD source distribution

source.done: $(OPENOCD_DIST)
	tar xzf $(OPENOCD_DIST)
	touch $@

# Compile OpenOCD

compile.done: source.done
	cd $(OPENOCD_SRC) ; ./configure --prefix=$(OPENOCD_DEST) --enable-ft2232-libftdi --enable-jlink --enable-rlink --enable-ulink --enable-vsllink --enable-arm-jtag-ew --enable-buspirate CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"
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
