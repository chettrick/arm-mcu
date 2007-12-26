# Download and build GNU toolchain for ARM microcontrollers

# $Id: Makefile,v 1.8 2007-12-26 14:08:49 cvs Exp $

PKGNAME		= arm-tools
INSTBASE	= $(shell pwd)/$(PKGNAME)

TEMP		= /tmp

BINUTILVER	= 2.18
BINUTILSERVER	= ftp://ftp.gnu.org/pub/gnu/binutils
BINUTILDIST	= $(TEMP)/binutils-$(BINUTILVER).tar.gz
BINUTILURL	= $(BINUTILSERVER)/`basename $(BINUTILDIST)`
BINUTILSRC	= binutils-$(BINUTILVER)

GCCVER		= 4.2.2
GCCSERVER	= ftp://ftp.gnu.org/pub/gnu/gcc/gcc-$(GCCVER)
GCCDIST		= $(TEMP)/gcc-$(GCCVER).tar.bz2
GCCURL		= $(GCCSERVER)/`basename $(GCCDIST)`
GCCSRC		= gcc-$(GCCVER)

NEWLIBVER	= 1.16.0
NEWLIBSERVER	= ftp://sources.redhat.com/pub/newlib
NEWLIBDIST	= $(TEMP)/newlib-$(NEWLIBVER).tar.gz
NEWLIBURL	= $(NEWLIBSERVER)/`basename $(NEWLIBDIST)`
NEWLIBSRC	= newlib-$(NEWLIBVER)

GDBVER		= 6.7.1
GDBSERVER	= ftp://sourceware.org/pub/insight/releases
GDBDIST		= $(TEMP)/insight-$(GDBVER).tar.bz2
GDBURL		= $(GDBSERVER)/`basename $(GDBDIST)`
GDBSRC		= insight-$(GDBVER)

ifeq ($(shell uname), CYGWIN_NT-5.1)
D2XXURL		= http://www.ftdichip.com/Driver/CDM/CDM 2.02.04 WHQL Certified.zip
D2XXDIST	= $(TEMP)/CDM 2.02.04 WHQL Certified.zip
endif
ifeq ($(shell uname), Linux)
D2XXURL		= http://www.ftdichip.com/Drivers/D2XX/Linux/libftd2xx0.4.13.tar.gz
D2XXDIST	= $(TEMP)/libftd2xx0.4.13.tar.gz
endif
D2XXSRC		= D2XX

OPENOCDSRC	= trunk

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
	cd $(BINUTILSRC) && ./configure --prefix=$(INSTBASE) --target=arm-elf --enable-interwork --enable-multilib
	$(MAKE) -C $(BINUTILSRC)
	$(MAKE) -C $(BINUTILSRC) install
	touch binutils.done

################################################################################

# Download gcc

$(GCCDIST):
	wget -P $(TEMP) $(GCCURL)

# Compile gcc

gcc.done: binutils.done $(GCCDIST)
	rm -rf $(GCCSRC)
	tar xjf $(GCCDIST)
	cd $(GCCSRC) && ./configure --prefix=$(INSTBASE) --target=arm-elf --enable-interwork --enable-multilib --enable-languages=c --disable-libssp --disable-libgomp
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCSRC)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCSRC) install
	touch gcc.done

################################################################################

# Download newlib

$(NEWLIBDIST):
	wget -P $(TEMP) $(NEWLIBURL)

# Compile newlib

newlib.done: gcc.done $(NEWLIBDIST)
	rm -rf $(NEWLIBSRC)
	tar xzf $(NEWLIBDIST)
	export PATH=$$PATH':'$(INSTBASE)/bin && cd $(NEWLIBSRC) && ./configure --prefix=$(INSTBASE) --target=arm-elf --enable-interwork --enable-multilib --disable-newlib-supplied-syscalls
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
	cd $(GDBSRC) && ./configure --prefix=$(INSTBASE) --target=arm-elf --enable-interwork --enable-multilib --disable-libssp
	$(MAKE) -C $(GDBSRC)
	$(MAKE) -C $(GDBSRC) install
	touch gdb.done

################################################################################

# Compile lpc21isp

lpc21isp.done: lpc21isp.c
	gcc -Wall -o lpc21isp lpc21isp.c
	install -csm 0755 lpc21isp $(INSTBASE)/bin
	touch lpc21isp.done

################################################################################

# Download FT2232 driver

$(D2XXSRC):
	wget -P $(TEMP) '$(D2XXURL)'
ifeq ($(shell uname), CYGWIN_NT-5.1)
	unzip '$(D2XXDIST)'
	mv CDM* $(D2XXSRC)
	cd $(D2XXSRC) && ln -s i386/ftd2xx.lib
endif
ifeq ($(shell uname), Linux)
	mkdir $(D2XXSRC)
	cd $(D2XXSRC) && tar xzf $(D2XXDIST)
	cd $(D2XXSRC)/static_lib && ln -s lib* libftd2xx.a
endif

# Install OpenOCD

openocd.done: $(D2XXSRC)
	svn checkout http://svn.berlios.de/svnroot/repos/openocd/trunk
	cd $(OPENOCDSRC) && ./bootstrap
	cd $(OPENOCDSRC) && ./configure --enable-ft2232_ftd2xx --disable-ft2232_libftdi --disable-amtjtagaccel --disable-ep93xx --disable-parport --disable-parport_ppdev --with-ftd2xx=`pwd`/../$(D2XXSRC)
ifeq ($(shell uname), CYGWIN_NT-5.1)
	$(MAKE) -C $(OPENOCDSRC)
endif
ifeq ($(shell uname), Linux)
	$(MAKE) -C $(OPENOCDSRC) LDFLAGS="-L`pwd`/$(D2XXSRC)/static_lib" LIBS=" -lpthread -ldl --static"
endif
	install -csm 0755 $(OPENOCDSRC)/src/openocd $(INSTBASE)/bin
	touch openocd.done

################################################################################

# Create installation tarball

$(TARBALL): binutils.done gcc.done newlib.done gdb.done lpc21isp.done openocd.done
	echo "GNU ARM microcontroller toolchain"	>$(INSTBASE)/README
	echo " "					>>$(INSTBASE)/README
	echo "Built on `date` from:"			>>$(INSTBASE)/README
	echo " "					>>$(INSTBASE)/README
	echo "$(BINUTILSRC)"				>>$(INSTBASE)/README
	echo "$(GCCSRC)"				>>$(INSTBASE)/README
	echo "$(NEWLIBSRC)"				>>$(INSTBASE)/README
	echo "$(GDBSRC)"				>>$(INSTBASE)/README
	awk '/define VERSION/ { printf("lpc21isp-%s\n", substr($$3, 2, length($$3)-2)); }' lpc21isp.c >>$(INSTBASE)/README
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
	-rm lpc21isp
	-rm lpc21isp.exe
	-rm $(PKGNAME)*.tgz
	rm -rf $(INSTBASE)
	rm -rf $(BINUTILSRC)
	rm -rf $(GCCSRC)
	rm -rf $(NEWLIBSRC)
	rm -rf $(GDBSRC)
	rm -rf $(D2XXSRC)
	rm -rf $(OPENOCDSRC)
