# Download and build GNU toolchain for ARM microcontrollers

# $Id: Makefile,v 1.37 2009-05-12 08:29:15 cvs Exp $

PKGNAME		= arm-tools
INSTBASE	= $(shell pwd)/$(PKGNAME)
TEMP		= /tmp
TARGETNAME	= arm-elf

BINUTILVER	= 2.19.1
BINUTILSERVER	= ftp://ftp.gnu.org/pub/gnu/binutils
BINUTILDIST	= $(TEMP)/binutils-$(BINUTILVER).tar.gz
BINUTILURL	= $(BINUTILSERVER)/`basename $(BINUTILDIST)`
BINUTILSRC	= binutils-$(BINUTILVER)

GCCVER		= 4.4.0
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

GDBVER		= 6.8
GDBSERVER	= ftp://sourceware.org/pub/insight/releases
GDBDIST		= $(TEMP)/insight-$(GDBVER).tar.bz2
GDBURL		= $(GDBSERVER)/`basename $(GDBDIST)`
GDBSRC		= insight-$(GDBVER)

LPC21ISPVER	= 1.64
LPC21ISPSERVER	= http://downloads.sourceforge.net/lpc21isp
LPC21ISPDIST	= $(TEMP)/lpc21isp-$(LPC21ISPVER).tar.gz
LPC21ISPURL	= $(LPC21ISPSERVER)/`basename $(LPC21ISPDIST)`
LPC21ISPSRC	= lpc21isp-$(LPC21ISPVER)

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

# Download lpc21isp

$(LPC21ISPDIST):
	wget -O $(LPC21ISPDIST) $(LPC21ISPURL)

# Compile lpc21isp

lpc21isp.done: $(LPC21ISPDIST)
	rm -rf $(LPC21ISPSRC)
	tar xzf $(LPC21ISPDIST)
	$(MAKE) -C $(LPC21ISPSRC) clean lpc21isp CFLAGS="-Wall -static"
	mkdir -p $(INSTBASE)/bin
	install -csm 0755 $(LPC21ISPSRC)/lpc21isp $(INSTBASE)/bin
	touch lpc21isp.done

################################################################################

# Create installation tarball

$(TARBALL): binutils.done gcc.done newlib.done newlibdocs.done gdb.done lpc21isp.done
	echo "GNU ARM microcontroller toolchain"	>$(INSTBASE)/README.txt
	echo " "					>>$(INSTBASE)/README.txt
	echo "Built on `date` from:"			>>$(INSTBASE)/README.txt
	echo " "					>>$(INSTBASE)/README.txt
	echo "$(BINUTILSRC)"				>>$(INSTBASE)/README.txt
	echo "$(GCCSRC)"				>>$(INSTBASE)/README.txt
	echo "$(NEWLIBSRC)"				>>$(INSTBASE)/README.txt
	echo "$(GDBSRC)"				>>$(INSTBASE)/README.txt
	echo "$(LPC21ISPSRC)"				>>$(INSTBASE)/README.txt
	unix2dos $(INSTBASE)/README.txt
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
