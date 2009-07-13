# Download and build OpenOCD JTAG for ARM microcontrollers

# $Id$

PKGNAME         = openocd
INSTBASE        = $(shell pwd)/$(PKGNAME)
TEMP            = /tmp

ifeq ($(shell uname), CYGWIN_NT-5.1)
D2XXVER		= 2.04.06
D2XXSERVER	= http://www.ftdichip.com/Driver/CDM
D2XXDIST	= $(TEMP)/CDM_$(D2XXVER)_WHQL_Certified.zip
D2XXURL		= $(D2XXSERVER)/CDM%20$(D2XXVER)%20WHQL%20Certified.zip
D2XXDIR		= d2xx-$(D2XXVER)
else
D2XXVER		= 0.4.16
D2XXSERVER	= http://www.ftdichip.com/Drivers/D2XX/Linux
D2XXDIST	= $(TEMP)/libftd2xx$(D2XXVER).tar.gz
D2XXURL		= $(D2XXSERVER)/`basename $(D2XXDIST)`
D2XXDIR		= libftd2xx$(D2XXVER)
endif

OPENOCDNAME	= openocd
OPENOCDVER	= 0.1.0
OPENOCDSERVER	= http://download.berlios.de/openocd
OPENOCDDIST	= $(TEMP)/$(OPENOCDNAME)-$(OPENOCDVER).tar.gz
OPENOCDURL	= $(OPENOCDSERVER)/`basename $(OPENOCDDIST)`
OPENOCDSRC	= $(OPENOCDNAME)-$(OPENOCDVER)

TARBALL		= $(OPENOCDNAME)-$(OPENOCDVER).tgz

.PHONY: default tarball rpm clean distclean

default: tarball

################################################################################

# Download FT2232 driver

$(D2XXDIST):
	wget -O $(D2XXDIST) $(D2XXURL)

# Unpack FT2232 driver

d2xx.done: $(D2XXDIST)
ifeq ($(shell uname), CYGWIN_NT-5.1)
	unzip $(D2XXDIST)
	mv CDM* $(D2XXDIR)
else
	tar xzf $(D2XXDIST)
endif
	touch d2xx.done

################################################################################

# Download OpenOCD

$(OPENOCDDIST):
	wget -O $(OPENOCDDIST) $(OPENOCDURL)

# Compile OpenOCD

openocd.done: d2xx.done $(OPENOCDDIST)
	rm -rf $(OPENOCDSRC)
	tar xzf $(OPENOCDDIST)
	cd $(OPENOCDSRC); patch -p0 <../openocd.patch
ifeq ($(shell uname), CYGWIN_NT-5.1)
	install -cm 755 $(D2XXDIR)/i386/ftd2xx.dll $(OPENOCDSRC)
	cd $(OPENOCDSRC) && ./configure -v --prefix=$(INSTBASE) --enable-ft2232_ftd2xx --with-ftd2xx-win32-zipdir=`pwd`/../$(D2XXDIR)
else
	cd $(OPENOCDSRC) && ./configure --prefix=$(INSTBASE) --enable-ft2232_ftd2xx --with-ftd2xx-linux-tardir=`pwd`/../$(D2XXDIR)
endif
	$(MAKE) -C $(OPENOCDSRC)
	$(MAKE) -C $(OPENOCDSRC) install
	$(MAKE) -C $(OPENOCDSRC) pdf
	mkdir -p $(INSTBASE)/doc
	install -cm 0644 $(OPENOCDSRC)/doc/openocd.pdf $(INSTBASE)/doc
	touch openocd.done

################################################################################

# Create tarball

$(TARBALL): openocd.done
	chmod -R -w $(INSTBASE)
	tar czf $(TARBALL) openocd
	chmod -R +w $(INSTBASE)

tarball: $(TARBALL)

################################################################################

# Create RPM package

fakeroot: openocd.done
	mkdir -p fakeroot/usr/local/bin
	cp -R -p openocd fakeroot/usr/local
	ln -s ../openocd/bin/openocd fakeroot/usr/local/bin/openocd
	
specfile: specfile.template fakeroot
	sed s/@@VERSION@@/$(OPENOCDVER)/g <specfile.template >specfile
	find fakeroot -type d | awk '/openocd/ { printf("%%dir %s\n", substr($$1, 9)); }' >>specfile
	find fakeroot -type f | cut -c 9- >>specfile
	find fakeroot -type l | cut -c 9- >>specfile

rpm: fakeroot specfile 
	mkdir -p rpmbuild/RPMS/$(MACHTYPE)
	chmod -R -w fakeroot
	rpmbuild --buildroot=`pwd`/fakeroot --define="_topdir `pwd`/rpmbuild" -bb specfile
	cp rpmbuild/RPMS/$(MACHTYPE)/*.rpm .
	chmod -R +w fakeroot

################################################################################

# Clean out working files

clean:
	-rm *.done
	-rm $(TARBALL)
	-rm -rf $(D2XXDIR)
	-rm -rf $(OPENOCDSRC)
	-rm -rf $(INSTBASE)
	-rm -rf fakeroot
	-rm -rf rpmbuild
	-rm specfile
	-rm *.rpm

distclean: clean
	rm $(D2XXDIST)
	rm $(OPENOCDDIST)
