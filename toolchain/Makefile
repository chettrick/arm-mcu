# Download and build GNU toolchain for ARM microcontrollers

# $Id: Makefile,v 1.30 2009-02-24 16:03:22 cvs Exp $

PKGNAME		= arm-tools
INSTBASE	= $(shell pwd)/$(PKGNAME)
TEMP		= /tmp
TARGETNAME	= arm-elf

BINUTILVER	= 2.19.1
BINUTILSERVER	= ftp://ftp.gnu.org/pub/gnu/binutils
BINUTILDIST	= $(TEMP)/binutils-$(BINUTILVER).tar.gz
BINUTILURL	= $(BINUTILSERVER)/`basename $(BINUTILDIST)`
BINUTILSRC	= binutils-$(BINUTILVER)

GCCVER		= 4.3.3
GCCSERVER	= ftp://ftp.gnu.org/pub/gnu/gcc/gcc-$(GCCVER)
GCCDIST		= $(TEMP)/gcc-$(GCCVER).tar.bz2
GCCURL		= $(GCCSERVER)/`basename $(GCCDIST)`
GCCSRC		= gcc-$(GCCVER)
GCCOBJ		= gcc-$(GCCVER).obj

NEWLIBVER	= 1.17.0
NEWLIBSERVER	= ftp://sources.redhat.com/pub/newlib
NEWLIBDIST	= $(TEMP)/newlib-$(NEWLIBVER).tar.gz
NEWLIBURL	= $(NEWLIBSERVER)/`basename $(NEWLIBDIST)`
NEWLIBSRC	= newlib-$(NEWLIBVER)
LIBCPDFURL	= $(NEWLIBSERVER)/libc.pdf
LIBMPDFURL	= $(NEWLIBSERVER)/libm.pdf
LIBCPDF		= $(TEMP)/libc.pdf
LIBMPDF		= $(TEMP)/libm.pdf

LPC21ISPVER	= 163
LPC21ISPSRC	= lpc21isp_$(LPC21ISPVER)
LPC21ISPDIST	= $(LPC21ISPSRC).zip

GDBVER		= 6.8
GDBSERVER	= ftp://sourceware.org/pub/insight/releases
GDBDIST		= $(TEMP)/insight-$(GDBVER).tar.bz2
GDBURL		= $(GDBSERVER)/`basename $(GDBDIST)`
GDBSRC		= insight-$(GDBVER)

ifeq ($(shell uname), CYGWIN_NT-5.1)
D2XXVER		= 2.04.06
D2XXSERVER	= http://www.ftdichip.com/Driver/CDM
D2XXDIST	= $(TEMP)/CDM_$(D2XXVER)_WHQL_Certified.zip
D2XXURL		= $(D2XXSERVER)/CDM/CDM%202.04.06%20WHQL%20Certified.zip
D2XXDIR		= d2xx-$(D2XXVER)
endif
ifeq ($(shell uname), Linux)
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

ifeq ($(shell uname), CYGWIN_NT-5.1)
TARBALL		= $(PKGNAME)-cygwin.tgz
else
TARBALL		= $(PKGNAME)-$(shell uname -s)-$(shell uname -i).tgz
endif

default: $(TARBALL)

################################################################################

# Download binutils

$(BINUTILDIST):
	wget -P $(TEMP) $(BINUTILURL)

# Compile binutils

binutils.done: $(BINUTILDIST)
	rm -rf $(BINUTILSRC)
	tar xzf $(BINUTILDIST)
	cd $(BINUTILSRC) && ./configure --prefix=$(INSTBASE) --target=$(TARGETNAME) --enable-interwork --enable-multilib --disable-nls --disable-shared --with-float=soft
	$(MAKE) -C $(BINUTILSRC)
ifeq ($(shell uname), Linux)
# Force static linking
	rm $(BINUTILSRC)/binutils/ar
	rm $(BINUTILSRC)/binutils/addr2line
	rm $(BINUTILSRC)/binutils/cxxfilt
	rm $(BINUTILSRC)/binutils/nm-new
	rm $(BINUTILSRC)/binutils/objcopy
	rm $(BINUTILSRC)/binutils/objdump
	rm $(BINUTILSRC)/binutils/ranlib
	rm $(BINUTILSRC)/binutils/readelf
	rm $(BINUTILSRC)/binutils/size
	rm $(BINUTILSRC)/binutils/strings
	rm $(BINUTILSRC)/binutils/strip-new
	rm $(BINUTILSRC)/gas/as-new
	rm $(BINUTILSRC)/gprof/gprof
	rm $(BINUTILSRC)/ld/ld-new
	$(MAKE) -C $(BINUTILSRC) LDFLAGS=-all-static
endif
	$(MAKE) -C $(BINUTILSRC) install
	touch binutils.done

################################################################################

# Download gcc

$(GCCDIST):
	wget -P $(TEMP) $(GCCURL)

# Compile gcc

# CentOS 4 wants GCCEXTRACONFIG=--with-mpfr=/usr/local

gcc.done: binutils.done $(GCCDIST)
	rm -rf $(GCCSRC)
	rm -rf $(GCCOBJ)
	tar xjf $(GCCDIST)
	mkdir -p $(GCCOBJ)
	cd $(GCCOBJ) && ../$(GCCSRC)/configure --prefix=$(INSTBASE) --target=$(TARGETNAME) --enable-interwork --enable-multilib --enable-languages=c --disable-libssp --disable-libgomp --disable-nls --disable-shared --with-newlib --with-float=soft $(GCCEXTRACONFIG)
ifeq ($(shell uname), Linux)
# Force static linking
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCOBJ) LDFLAGS=-static
else
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCOBJ)
endif
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCOBJ) install
	touch gcc.done

################################################################################

# Download newlib

$(NEWLIBDIST):
	wget -P $(TEMP) $(NEWLIBURL)

# Compile newlib

newlib.done: gcc.done $(NEWLIBDIST) $(LIBCPDF) $(LIBMPDF)
	rm -rf $(NEWLIBSRC)
	tar xzf $(NEWLIBDIST)
	export PATH=$$PATH':'$(INSTBASE)/bin && cd $(NEWLIBSRC) && ./configure --prefix=$(INSTBASE) --target=$(TARGETNAME) --enable-interwork --enable-multilib --disable-newlib-supplied-syscalls --disable-nls --disable-shared --with-float=soft
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(NEWLIBSRC)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(NEWLIBSRC) install
	
	touch newlib.done

# Download newlib docs

$(LIBCPDF):
	wget -P $(TEMP) $(LIBCPDFURL)

$(LIBMPDF):
	wget -P $(TEMP) $(LIBMPDFURL)

# Install newlib docs

newlibdocs.done: $(LIBCPDF) $(LIBMPDF)
	mkdir -p $(INSTBASE)/doc
	install -cm 0444 $(LIBCPDF) $(INSTBASE)/doc
	install -cm 0444 $(LIBMPDF) $(INSTBASE)/doc
	touch newlibdocs.done

################################################################################

# Download gdb

$(GDBDIST):
	wget -P $(TEMP) $(GDBURL)

# Compile gdb

gdb.done: $(GDBDIST)
	rm -rf $(GDBSRC)
	tar xjf $(GDBDIST)
	cd $(GDBSRC) && ./configure --prefix=$(INSTBASE) --target=$(TARGETNAME) --enable-interwork --enable-multilib --disable-libssp --disable-nls --disable-shared
	$(MAKE) -C $(GDBSRC)
	$(MAKE) -C $(GDBSRC) install
	touch gdb.done

################################################################################

# Download FT2232 driver

$(D2XXDIST):
	wget -O $(D2XXDIST) $(D2XXURL)

# Unpack FT2232 driver

d2xx.done: $(D2XXDIST)
ifeq ($(shell uname), CYGWIN_NT-5.1)
	unzip $(D2XXDIST)
	mv CDM* $(D2XXDIR)
	cd $(D2XXDIR) && ln -s i386/ftd2xx.lib
endif
ifeq ($(shell uname), Linux)
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
ifeq ($(shell uname), CYGWIN_NT-5.1)
	cd $(OPENOCDSRC) && ./configure --enable-ft2232_ftd2xx --disable-ft2232_libftdi --disable-amtjtagaccel --disable-ep93xx --disable-parport --disable-parport_ppdev --with-ftd2xx=`pwd`/../$(D2XXLIBDIR)
	$(MAKE) -C $(OPENOCDSRC)
endif
ifeq ($(shell uname), Linux)
#	cd $(OPENOCDSRC) && ./configure --enable-ft2232_ftd2xx --disable-ft2232_libftdi --disable-amtjtagaccel --disable-ep93xx --disable-parport --disable-parport_ppdev --with-ftd2xx-linux-tardir=`pwd`/../$(D2XXDIR)
	cd $(OPENOCDSRC) && ./configure --prefix=$(INSTBASE) --enable-ft2232_ftd2xx --with-ftd2xx-linux-tardir=`pwd`/../$(D2XXDIR)
endif
	$(MAKE) -C $(OPENOCDSRC)
	$(MAKE) -C $(OPENOCDSRC) install
	$(MAKE) -C $(OPENOCDSRC) pdf
	mkdir -p $(INSTBASE)/doc
	install -cm 0644 $(OPENOCDSRC)/doc/openocd.pdf $(INSTBASE)/doc
	touch openocd.done

################################################################################

# Compile lpc21isp

lpc21isp.done: $(LPC21ISPDIST)
	rm -rf $(LPC21ISPSRC)
	mkdir -p $(LPC21ISPSRC)
	unzip $(LPC21ISPDIST) -d $(LPC21ISPSRC)
	$(MAKE) -C $(LPC21ISPSRC) CFLAGS="-Wall -static"
	mkdir -p $(INSTBASE)/bin
	install -csm 0755 $(LPC21ISPSRC)/lpc21isp $(INSTBASE)/bin
	touch lpc21isp.done

################################################################################

# Create installation tarball

$(TARBALL): binutils.done gcc.done newlib.done newlibdocs.done gdb.done openocd.done lpc21isp.done
	echo "GNU ARM microcontroller toolchain"	>$(INSTBASE)/README
	echo " "					>>$(INSTBASE)/README
	echo "Built on `date` from:"			>>$(INSTBASE)/README
	echo " "					>>$(INSTBASE)/README
	echo "$(BINUTILSRC)"				>>$(INSTBASE)/README
	echo "$(GCCSRC)"				>>$(INSTBASE)/README
	echo "$(NEWLIBSRC)"				>>$(INSTBASE)/README
	echo "$(GDBSRC)"				>>$(INSTBASE)/README
	echo "$(OPENOCDSRC)"				>>$(INSTBASE)/README
	echo "$(LPC21ISPSRC)"				>>$(INSTBASE)/README
	chmod -R ugo-w $(INSTBASE)
ifeq ($(shell uname), Linux)
	sudo chown -R 0.0 $(INSTBASE)
endif
	tar czf $(TARBALL) `basename $(INSTBASE)`
ifeq ($(shell uname), Linux)
	sudo chown -R $(shell id -u).$(shell id -g) $(INSTBASE)
endif
	chmod -R u+w $(INSTBASE)

# Store tarball to repository

store: $(TARBALL)
	scp $(TARBALL) root@munts.net:/export/software/MCU

# Install tarball to /usr/local

install: $(TARBALL)
	tar xzf $(TARBALL) --directory=/usr/local

# Uninstall

uninstall:
	rm -rf /usr/local/$(PKGNAME)

# Clean out working files

clean:
	-rm *.done
	-rm *.tgz
	rm -rf $(INSTBASE)
	rm -rf $(BINUTILSRC)
	rm -rf $(GCCSRC)
	rm -rf $(GCCOBJ)
	rm -rf $(NEWLIBSRC)
	rm -rf $(GDBSRC)
	rm -rf $(LPC21ISPSRC)
	rm -rf $(D2XXDIR)
	rm -rf $(OPENOCDSRC)
