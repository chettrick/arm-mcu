# Download and build GNU toolchain for ARM microcontrollers

# $Id: Makefile,v 1.24 2008-11-20 18:43:48 cvs Exp $

PKGNAME		= arm-tools
INSTBASE	= $(shell pwd)/$(PKGNAME)
TEMP		= /tmp
TARGETNAME	= arm-elf

BINUTILVER	= 2.19
BINUTILSERVER	= ftp://ftp.gnu.org/pub/gnu/binutils
BINUTILDIST	= $(TEMP)/binutils-$(BINUTILVER).tar.gz
BINUTILURL	= $(BINUTILSERVER)/`basename $(BINUTILDIST)`
BINUTILSRC	= binutils-$(BINUTILVER)

GCCVER		= 4.3.2
GCCSERVER	= ftp://ftp.gnu.org/pub/gnu/gcc/gcc-$(GCCVER)
GCCDIST		= $(TEMP)/gcc-$(GCCVER).tar.bz2
GCCURL		= $(GCCSERVER)/`basename $(GCCDIST)`
GCCSRC		= gcc-$(GCCVER)
GCCOBJ		= gcc-$(GCCVER).obj

NEWLIBVER	= 1.16.0
NEWLIBSERVER	= ftp://sources.redhat.com/pub/newlib
NEWLIBDIST	= $(TEMP)/newlib-$(NEWLIBVER).tar.gz
NEWLIBURL	= $(NEWLIBSERVER)/`basename $(NEWLIBDIST)`
NEWLIBSRC	= newlib-$(NEWLIBVER)

LPC21ISPVER	= 160
LPC21ISPSRC	= lpc21isp_$(LPC21ISPVER)
LPC21ISPDIST	= $(LPC21ISPSRC).zip

GDBVER		= 6.8
GDBSERVER	= ftp://sourceware.org/pub/insight/releases
GDBDIST		= $(TEMP)/insight-$(GDBVER).tar.bz2
GDBURL		= $(GDBSERVER)/`basename $(GDBDIST)`
GDBSRC		= insight-$(GDBVER)

ifeq ($(shell uname), CYGWIN_NT-5.1)
D2XXURL		= http://www.ftdichip.com/Driver/CDM/CDM%202.04.06%20WHQL%20Certified.zip
D2XXDIST	= $(TEMP)/CDM_2.04.06_WHQL_Certified.zip
endif
ifeq ($(shell uname), Linux)
D2XXURL		= http://www.ftdichip.com/Drivers/D2XX/Linux/libftd2xx0.4.13.tar.gz
D2XXDIST	= $(TEMP)/libftd2xx0.4.13.tar.gz
endif
D2XXDIR		= D2XX

OPENOCDVER	= 717
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

newlib.done: gcc.done $(NEWLIBDIST)
	rm -rf $(NEWLIBSRC)
	tar xzf $(NEWLIBDIST)
	export PATH=$$PATH':'$(INSTBASE)/bin && cd $(NEWLIBSRC) && ./configure --prefix=$(INSTBASE) --target=$(TARGETNAME) --enable-interwork --enable-multilib --disable-newlib-supplied-syscalls --disable-nls --disable-shared --with-float=soft
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(NEWLIBSRC)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(NEWLIBSRC) install
	touch newlib.done

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
	mkdir $(D2XXDIR)
	cd $(D2XXDIR) && tar xzf $(D2XXDIST)
	cd $(D2XXDIR)/static_lib && ln -s lib* libftd2xx.a
endif
	touch d2xx.done

# Compile OpenOCD

openocd.done: d2xx.done
	svn checkout -r $(OPENOCDVER) http://svn.berlios.de/svnroot/repos/openocd/trunk $(OPENOCDSRC)
	cd $(OPENOCDSRC) && ./bootstrap
	cd $(OPENOCDSRC) && ./configure --enable-ft2232_ftd2xx --disable-ft2232_libftdi --disable-amtjtagaccel --disable-ep93xx --disable-parport --disable-parport_ppdev --with-ftd2xx=`pwd`/../$(D2XXDIR)
ifeq ($(shell uname), CYGWIN_NT-5.1)
	$(MAKE) -C $(OPENOCDSRC)
endif
ifeq ($(shell uname), Linux)
	$(MAKE) -C $(OPENOCDSRC) LDFLAGS="-L`pwd`/$(D2XXDIR)/static_lib" LIBS=" -lpthread -ldl -static"
endif
	install -csm 0755 $(OPENOCDSRC)/src/openocd $(INSTBASE)/bin
	touch openocd.done

################################################################################

# Compile lpc21isp

lpc21isp.done: $(LPC21ISPDIST)
	rm -rf $(LPC21ISPSRC)
	mkdir -p $(LPC21ISPSRC)
	unzip $(LPC21ISPDIST) -d $(LPC21ISPSRC)
	$(MAKE) -C $(LPC21ISPSRC) CFLAGS="-Wall -static"
	install -csm 0755 $(LPC21ISPSRC)/lpc21isp $(INSTBASE)/bin
	touch lpc21isp.done

################################################################################

# Create installation tarball

$(TARBALL): binutils.done gcc.done newlib.done gdb.done openocd.done lpc21isp.done
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
