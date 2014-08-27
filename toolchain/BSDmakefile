# Download and build GNU toolchain for ARM microcontrollers

# $Id$

# Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

ABI		?= eabi
ifeq ($(ABI), elf)
TARGETNAME	= arm-elf
PKGNAME		= arm-elf-tools
GCCEXTRACONFIG	+= --enable-obsolete
else
TARGETNAME	= arm-none-eabi
PKGNAME		= arm-mcu-tools
endif
INSTBASE	= $(shell pwd)/$(PKGNAME)

FIND		= find
TAR		= tar
TEMP		= $(shell pwd)

ifeq ($(shell uname), OpenBSD)
FTP		= ftp
else
FTP		= wget
endif

GNUSERVER	= http://ftp.gnu.org/pub/gnu

BINUTILS	= binutils
BINUTILVER	= 2.24
BINUTILSRC	= $(BINUTILS)-$(BINUTILVER)
BINUTILSERVER	= $(GNUSERVER)/$(BINUTILS)
BINUTILDIST	= $(TEMP)/$(BINUTILSRC).tar.bz2
BINUTILURL	= $(BINUTILSERVER)/$(BINUTILSRC).tar.bz2
BINUTILBLD	= build/$(BINUTILSRC)

GCC		= gcc
GCCVER		= 4.8.2
GCCSRC		= $(GCC)-$(GCCVER)
GCCSERVER	= $(GNUSERVER)/$(GCC)/$(GCCSRC)
GCCDIST		= $(TEMP)/$(GCCSRC).tar.bz2
GCCURL		= $(GCCSERVER)/$(GCCSRC).tar.bz2
GCCBLD		= build/$(GCCSRC)

NEWLIB		= newlib
NEWLIBVER	= 2.1.0
NEWLIBSRC	= $(NEWLIB)-$(NEWLIBVER)
NEWLIBSERVER	= http://mirrors.kernel.org/sources.redhat.com/$(NEWLIB)
NEWLIBDIST	= $(TEMP)/$(NEWLIBSRC).tar.gz
NEWLIBURL	= $(NEWLIBSERVER)/$(NEWLIBSRC).tar.gz
NEWLIBBLD	= build/$(NEWLIBSRC)

LIBCPDFURL	= $(NEWLIBSERVER)/libc.pdf
LIBMPDFURL	= $(NEWLIBSERVER)/libm.pdf
LIBCPDF		= $(TEMP)/libc.pdf
LIBMPDF		= $(TEMP)/libm.pdf

GDB		= gdb
GDBVER		= 7.7
GDBSRC		= $(GDB)-$(GDBVER)
GDBSERVER	= $(GNUSERVER)/$(GDB)
GDBDIST		= $(TEMP)/$(GDBSRC).tar.bz2
GDBURL		= $(GDBSERVER)/$(GDBSRC).tar.bz2
GDBBLD		= build/$(GDBSRC)

VERSION		= $(BINUTILVER)_$(GCCVER)_$(NEWLIBVER)_$(GDBVER)
RELEASE		= 1

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
TARBALL		= $(PKGNAME)-$(VERSION)-cygwin.tgz
else
TARBALL		= $(PKGNAME)-$(VERSION)-$(shell uname -s)-$(shell uname -m).tgz
endif

ifeq ($(shell uname), OpenBSD)
GCCEXTRACONFIG	+= --with-gmp=/usr/local
GCCEXTRACONFIG	+= --with-mpc=/usr/local
GCCEXTRACONFIG	+= --with-mpfr=/usr/local
PACKAGENAME	= $(PKGNAME)-$(VERSION).tgz
endif

PKGARCH		= `dpkg --print-architecture`
PKGDIR		= $(PKGNAME)-$(VERSION)-debian7-$(PKGARCH)
PKGFILE		= $(PKGDIR).deb

default: readme.done

################################################################################

# Download all source distributions

download: $(BINUTILDIST) $(GCCDIST) $(NEWLIBDIST) $(GDBDIST) $(LIBCPDF) $(LIBMPDF)

################################################################################

# Unpack all source distributions

source.done: $(BINUTILDIST) $(GCCDIST) $(NEWLIBDIST) $(GDBDIST) $(LIBCPDF) $(LIBMPDF)
	$(TAR) xjf $(BINUTILDIST)
	$(TAR) xjf $(GCCDIST)
	if [ -f multilibs.$(ABI).patch ]; then cd $(GCCSRC) ; patch -b -p0 <../multilibs.$(ABI).patch ; fi
	$(TAR) xzf $(NEWLIBDIST)
	ln -s "../$(NEWLIBSRC)/newlib" $(GCCSRC)/newlib
	$(TAR) xjf $(GDBDIST)
	touch $@

################################################################################

# Download binutils

$(BINUTILDIST):
	$(FTP) $(BINUTILURL)

# Compile binutils

binutils.done: source.done
	rm -rf $(BINUTILBLD)
	mkdir -p $(BINUTILBLD)
	cd $(BINUTILBLD) && ../../$(BINUTILSRC)/configure --prefix=$(INSTBASE) --target=$(TARGETNAME) --enable-interwork --enable-multilib --enable-lto --disable-nls --disable-shared --with-float=soft --disable-werror
	$(MAKE) $(MAKEJOBS) -C $(BINUTILBLD)
	$(MAKE) -C $(BINUTILBLD) install
	touch $@

################################################################################

# Download gcc

$(GCCDIST):
	$(FTP) $(GCCURL)

# Compile gcc

gcc.done: binutils.done
	rm -rf $(GCCBLD)
	mkdir -p $(GCCBLD)
	cd $(GCCBLD) && ../../$(GCCSRC)/configure --prefix=$(INSTBASE) --target=$(TARGETNAME) --enable-interwork --enable-multilib --enable-lto --disable-nls --disable-shared --with-float=soft --disable-werror --enable-languages=c,c++ --disable-libssp --disable-libgomp --with-newlib --disable-libgloss --disable-newlib-supplied-syscalls --with-system-zlib $(GCCEXTRACONFIG)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) $(MAKEJOBS) -C $(GCCBLD)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCBLD) install
	touch $@

################################################################################

# Download newlib

$(NEWLIBDIST):
	$(FTP) $(NEWLIBURL)

# Note: newlib is built by gcc

# Download newlib docs

$(LIBCPDF):
	$(FTP) $(LIBCPDFURL)

$(LIBMPDF):
	$(FTP) $(LIBMPDFURL)

# Install newlib docs

newlibdocs.done: $(LIBCPDF) $(LIBMPDF)
	mkdir -p $(INSTBASE)/doc
	install -cm 0444 $(LIBCPDF) $(INSTBASE)/doc
	install -cm 0444 $(LIBMPDF) $(INSTBASE)/doc
	touch $@

################################################################################

# Download gdb

$(GDBDIST):
	$(FTP) $(GDBURL)

# Compile gdb

gdb.done: $(GDBDIST)
	test -f /usr/include/expat.h
	rm -rf $(GDBBLD)
	mkdir -p $(GDBBLD)
	cd $(GDBBLD) && ../../$(GDBSRC)/configure --prefix=$(INSTBASE) --target=$(TARGETNAME) --enable-interwork --enable-multilib --disable-libssp --disable-nls --disable-shared --disable-werror
	$(MAKE) $(MAKEJOBS) -C $(GDBBLD)
	$(MAKE) -C $(GDBBLD) install
	touch $@

################################################################################

# Create README.txt

readme.done: binutils.done gcc.done newlibdocs.done gdb.done
	echo "GNU ARM Microcontroller Toolchain"	>$(INSTBASE)/README.txt
	echo " "					>>$(INSTBASE)/README.txt
	echo "Built on `uname -a`"			>>$(INSTBASE)/README.txt
	echo "On `date` from:"				>>$(INSTBASE)/README.txt
	echo " "					>>$(INSTBASE)/README.txt
	echo "$(BINUTILSRC)"				>>$(INSTBASE)/README.txt
	echo "$(GCCSRC)"				>>$(INSTBASE)/README.txt
	echo "$(NEWLIBSRC)"				>>$(INSTBASE)/README.txt
	echo "$(GDBSRC)"				>>$(INSTBASE)/README.txt
	touch $@

################################################################################

# Create toolchain tarball

tarball: readme.done
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	$(TAR) czf $(TARBALL) `basename $(INSTBASE)` --mode=ugo-w
else
	$(TAR) czf $(TARBALL) `basename $(INSTBASE)` --owner=root --group=root --mode=ugo-w
endif

################################################################################

# Create Linux .deb package

ifeq ($(shell uname), Linux)
deb: readme.done
	mkdir -p					$(PKGDIR)/DEBIAN
	mkdir -p					$(PKGDIR)/usr/local
	install -cm 0444 control.template		$(PKGDIR)/DEBIAN/control
	sed -i s/@@ARCH@@/$(PKGARCH)/g			$(PKGDIR)/DEBIAN/control
	sed -i s/@@NAME@@/$(PKGNAME)/g			$(PKGDIR)/DEBIAN/control
	sed -i s/@@VERSION@@/$(VERSION)/g		$(PKGDIR)/DEBIAN/control
	sed -i /Version:/s/_/-/g			$(PKGDIR)/DEBIAN/control
	cp -R -P -p $(PKGNAME)				$(PKGDIR)/usr/local
	chmod -R ugo-w					$(PKGDIR)/usr/local
	fakeroot dpkg-deb --build			$(PKGDIR)
	chmod -R ugo+w					$(PKGDIR)/usr/local
endif

################################################################################

# Create Linux RPM package

ifeq ($(shell uname), Linux)
fakeroot: readme.done
	mkdir -p $@/usr/local
	cp -R -P -p $(PKGNAME) $@/usr/local

specfile: $@.template fakeroot
	sed s/@@PKGNAME@@/$(PKGNAME)/g <$@.template | sed s/@@VERSION@@/$(VERSION)/g | sed s/@@RELEASE@@/$(RELEASE)/g > $@
	$(FIND) fakeroot/usr/local/$(PKGNAME) -type d | awk '{ printf("%%dir /%s\n", substr($$1, 10)); }' >> $@
	$(FIND) fakeroot/usr/local/$(PKGNAME) -type f | cut -c 9- >> $@
	$(FIND) fakeroot/usr/local/$(PKGNAME) -type l | cut -c 9- >> $@

rpm: specfile
	rpmbuild --buildroot=`pwd`/fakeroot --define="_topdir `pwd`/rpmbuild" -bb specfile
	cp rpmbuild/RPMS/*/*.rpm .
endif

################################################################################

# Create OpenBSD package

ifeq ($(shell uname), OpenBSD)

fakeroot: readme.done
	mkdir -p $@/usr/local
	cp -R -P -p $(PKGNAME) $@/usr/local
# Why aren't these links already created on OpenBSD?
	ln -s liblto_plugin.so.0.0 $@/usr/local/$(PKGNAME)/libexec/gcc/arm-none-eabi/$(GCCVER)/liblto_plugin.so
	ln -s liblto_plugin.so.0.0 $@/usr/local/$(PKGNAME)/libexec/gcc/arm-none-eabi/$(GCCVER)/liblto_plugin.so.0

CONTENTS: fakeroot
	echo "@owner root"				> $@
	echo "@group wheel"				>> $@
	echo "@mode -w"					>> $@
	echo "@cwd /usr/local"				>> $@
	find fakeroot/usr/local/$(PKGNAME) -type d | awk '{ printf("@dir %s\n", substr($$1, 20)); }' >> $@
	find fakeroot -type f | cut -c 20- | sort	>> $@
	find fakeroot -type l | awk '{ printf("echo %s `readlink %s`\n", $$1, $$1); }' | sh | \
	awk '{ printf("@exec ln -s %s %s\n", $$2, substr($$1,9)); }'            >> $@
	find fakeroot -type l | awk '{ printf("@unexec rm %s\n", substr($$1, 9)); }' >> $@

COMMENT:
	echo "GNU ARM Microcontroller Toolchain"	> $@

$(PACKAGENAME): CONTENTS COMMENT
	pkg_create -A `uname -m` -f CONTENTS -D COMMENT="`cat COMMENT`" -d COMMENT -p / -B fakeroot $(PACKAGENAME)
	@-rm CONTENTS
	@-rm COMMENT

package: $(PACKAGENAME)
endif

################################################################################

# Clean out working files

clean:
	rm -rf $(INSTBASE)
	rm -rf $(BINUTILSRC)
	rm -rf $(GCCSRC)
	rm -rf $(NEWLIBSRC)
	rm -rf $(GDBSRC)
	rm -rf build fakeroot specfile rpmbuild *.done *.deb *.rpm *.tgz *.tar.bz2 *.tar.gz *.pdf $(PKGDIR)

distclean: clean

.PHONY: all clean deb default download fakeroot package specfile rpm tarball \
	binutils.done gcc.done gdb.done newlibdocs.done readme.done source.done
