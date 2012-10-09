# Makefile for building OpenOCD for Linux

# Get prebuilt Windows binaries from:
# http://www.freddiechopin.info/index.php/en/download/category/4-openocd

# $Id$

OPENOCD_NAME	= openocd
OPENOCD_VER	= 0.6.1
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
	cd $(OPENOCD_SRC) ; ./configure --prefix=/usr/local --enable-ft2232_libftdi $(EXTRACONFIG)
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
