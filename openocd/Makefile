# Download and build OpenOCD JTAG for ARM microcontrollers

# $Id: Makefile,v 1.1 2009-04-24 08:45:49 cvs Exp $

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

OPENOCDVER	= 0.1.0
OPENOCDSERVER	= http://download.berlios.de/openocd
OPENOCDDIST	= $(TEMP)/openocd-$(OPENOCDVER).tar.gz
OPENOCDURL	= $(OPENOCDSERVER)/`basename $(OPENOCDDIST)`
OPENOCDSRC	= openocd-$(OPENOCDVER)

TARBALL		= openocd-$(OPENOCDVER).tgz

default: $(TARBALL)

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
	cd $(OPENOCDSRC) && ./configure -v --prefix=$(INSTBASE) --enable-ft2232_ftd2xx --with-ftd2xx-win32-zipdir=`pwd`/../$(D2XXDIR) CC="gcc -mno-cygwin"
else
	cd $(OPENOCDSRC) && ./configure --prefix=$(INSTBASE) --enable-ft2232_ftd2xx --with-ftd2xx-linux-tardir=`pwd`/../$(D2XXDIR)
endif
	$(MAKE) -C $(OPENOCDSRC)
	$(MAKE) -C $(OPENOCDSRC) install
	$(MAKE) -C $(OPENOCDSRC) pdf
	mkdir -p $(INSTBASE)/doc
	install -cm 0644 $(OPENOCDSRC)/doc/openocd.pdf $(INSTBASE)/doc
	chmod -R -w $(INSTBASE)
	touch openocd.done

# Create tarball

$(TARBALL): openocd.done
	tar czf $(TARBALL) openocd

################################################################################

# Clean out working files

clean:
	-rm *.done
	-rm $(TARBALL)
	rm -rf $(D2XXDIR)
	rm -rf $(OPENOCDSRC)
	rm -rf $(INSTBASE)

distclean: clean
	rm $(D2XXDIST)
	rm $(OPENOCDDIST)
