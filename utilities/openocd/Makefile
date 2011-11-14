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
OPENOCD_DEST	= /usr/local/openocd-$(OPENOCD_VER)
OPENOCD_RELEASE	:= $(shell pwd)/$(OPENOCD_NAME)-$(OPENOCD_VER)-$(shell uname -s)-$(shell uname -m).tgz

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
	cd $(OPENOCD_SRC) ; ./configure --prefix=$(OPENOCD_DEST) --htmldir=$(OPENOCD_DEST)/share/doc --enable-ft2232-libftdi --enable-jlink --enable-rlink --enable-ulink --enable-vsllink --enable-arm-jtag-ew --enable-buspirate CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"
	$(MAKE) -C $(OPENOCD_SRC)
	$(MAKE) -C $(OPENOCD_SRC) html
	touch $@

# Install OpenOCD

install.done: compile.done
	rm -rf fakeroot
	$(MAKE) -C $(OPENOCD_SRC) install install-html DESTDIR=`pwd`/fakeroot
	mv fakeroot/usr/local/openocd-$(OPENOCD_VER)/share/doc/openocd.html/*.html fakeroot/usr/local/openocd-$(OPENOCD_VER)/share/doc
	rmdir fakeroot/usr/local/openocd-$(OPENOCD_VER)/share/doc/openocd.html
	rm -rf fakeroot/usr/local/openocd-$(OPENOCD_VER)/share/info
	rm -rf fakeroot/usr/local/openocd-$(OPENOCD_VER)/share/man
	touch $@

release.done: install.done
	chmod -R ugo-w fakeroot
	cd fakeroot/usr/local ; tar czf $(OPENOCD_RELEASE) * --owner=root --group=root
	chmod -R ugo+w fakeroot
	touch $@

# Clean out working files

clean:
	-$(MAKE) -C $(OPENOCD_SRC) clean
	-rm -rf fakeroot
	-rm $(OPENOCD_RELEASE)
	-rm compile.done
	-rm install.done
	-rm release.done

reallyclean: clean
	-rm -rf $(LIBFTDI_SRC)
	-rm -rf $(LIBFTDI_DEST)
	-rm -rf $(OPENOCD_SRC)
	-rm source.done

distclean: reallyclean
	-rm $(OPENOCD_DIST)
