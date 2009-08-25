# Download and build GNU toolchain for ARM microcontrollers

# $Id$

PKGNAME		= arm-tools
INSTBASE	= $(shell pwd)/$(PKGNAME)
TEMP		= /tmp
TARGETNAME	= arm-elf

BINUTILVER	= 2.19.1
BINUTILSERVER	= ftp://ftp.gnu.org/pub/gnu/binutils
BINUTILDIST	= $(TEMP)/binutils-$(BINUTILVER).tar.gz
BINUTILURL	= $(BINUTILSERVER)/`basename $(BINUTILDIST)`
BINUTILSRC	= binutils-$(BINUTILVER)

GCCVER		= 4.4.1
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

GDBVER		= 6.8-1
GDBSERVER	= ftp://sourceware.org/pub/insight/releases
GDBDIST		= $(TEMP)/insight-$(GDBVER).tar.bz2
GDBURL		= $(GDBSERVER)/`basename $(GDBDIST)`
GDBSRC		= insight-$(GDBVER)

VERSION		= $(BINUTILVER)_$(GCCVER)_$(NEWLIBVER)_$(subst -,.,$(GDBVER))
RELEASE		= 1

ifeq ($(shell uname), CYGWIN_NT-5.1)
TARBALL		= $(PKGNAME)-$(VERSION)-cygwin.tgz
else
TARBALL		= $(PKGNAME)-$(VERSION)-$(shell uname -s)-$(shell uname -i).tgz
endif

.PHONY: download tarball rpm clean distclean

ifeq ($(shell uname), Linux)
default: rpm
else
default: tarball
endif

################################################################################

# Download all source distributions

download: $(BINUTILDIST) $(GCCDIST) $(NEWLIBDIST) $(GDBDIST) $(LIBCPDF) $(LIBMPDF)

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
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCOBJ)
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
	cd $(GDBSRC) && patch -p0 <../gdb.patch
	cd $(GDBSRC) && ./configure --prefix=$(INSTBASE) --target=$(TARGETNAME) --enable-interwork --enable-multilib --disable-libssp --disable-nls --disable-shared
	$(MAKE) -C $(GDBSRC)
	$(MAKE) -C $(GDBSRC) install
	touch gdb.done

################################################################################

# Create README.txt

readme.done: binutils.done gcc.done newlib.done newlibdocs.done gdb.done
	echo "GNU ARM microcontroller toolchain"	>$(INSTBASE)/README.txt
	echo " "					>>$(INSTBASE)/README.txt
	echo "Built on `date` from:"			>>$(INSTBASE)/README.txt
	echo " "					>>$(INSTBASE)/README.txt
	echo "$(BINUTILSRC)"				>>$(INSTBASE)/README.txt
	echo "$(GCCSRC)"				>>$(INSTBASE)/README.txt
	echo "$(NEWLIBSRC)"				>>$(INSTBASE)/README.txt
	echo "$(GDBSRC)"				>>$(INSTBASE)/README.txt
	unix2dos $(INSTBASE)/README.txt
	touch readme.done

################################################################################

# Create toolchain tarball

tarball: readme.done
ifeq ($(shell uname), CYGWIN_NT-5.1)
	tar czf $(TARBALL) `basename $(INSTBASE)` --mode=ugo-w
else
	tar czf $(TARBALL) `basename $(INSTBASE)` --owner=root --group=root --mode=ugo-w
endif

################################################################################

# Create toolchain RPM package

fakeroot: readme.done
	mkdir -p fakeroot/usr/local
	cp -R -p arm-tools fakeroot/usr/local
	chmod -R -w fakeroot

specfile: specfile.template fakeroot
	sed s/@@VERSION@@/$(VERSION)/g <specfile.template | sed s/@@RELEASE@@/$(RELEASE)/g >specfile
	find fakeroot/usr/local/arm-tools -type d | awk '{ printf("%%dir /%s\n", substr($$1, 10)); }' >>specfile
	find fakeroot/usr/local/arm-tools -type f | cut -c 9- >>specfile

rpm: specfile
	mkdir -p rpmbuild/RPMS/$(MACHTYPE)
	rpmbuild --buildroot=`pwd`/fakeroot --define="_topdir `pwd`/rpmbuild" -bb specfile
	cp rpmbuild/RPMS/$(MACHTYPE)/*.rpm .

################################################################################

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
	rm -rf fakeroot specfile rpmbuild *.rpm

distclean: clean
