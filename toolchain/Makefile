# Download and build GNU toolchain for ARM microcontrollers

# $Id$

# Copyright (C)2013, Philip Munts, President, Munts AM Corp.
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
PKGNAME		= arm-mcu-elf-tools
GCCEXTRACONFIG	+= --enable-obsolete
else
TARGETNAME	= arm-none-eabi
PKGNAME		= arm-mcu-tools
endif
INSTBASE	= $(shell pwd)/$(PKGNAME)
TEMP		= /tmp
ifeq ($(shell uname), OpenBSD)
TAR		= gtar
else
TAR		= tar
FIND		= find
endif

BINUTILVER	= 2.23.2
BINUTILSERVER	= http://ftp.gnu.org/pub/gnu/binutils
BINUTILDIST	= $(TEMP)/binutils-$(BINUTILVER).tar.gz
BINUTILURL	= $(BINUTILSERVER)/`basename $(BINUTILDIST)`
BINUTILSRC	= binutils-$(BINUTILVER)
BINUTILBLD	= build/binutils-$(BINUTILVER)

GCCVER		= 4.7.3
GCCSERVER	= http://ftp.gnu.org/pub/gnu/gcc/gcc-$(GCCVER)
GCCDIST		= $(TEMP)/gcc-$(GCCVER).tar.bz2
GCCURL		= $(GCCSERVER)/`basename $(GCCDIST)`
GCCSRC		= gcc-$(GCCVER)
GCCBLD		= build/gcc-$(GCCVER)

NEWLIBVER	= 2.0.0
NEWLIBSERVER	= http://mirrors.kernel.org/sources.redhat.com/newlib
NEWLIBDIST	= $(TEMP)/newlib-$(NEWLIBVER).tar.gz
NEWLIBURL	= $(NEWLIBSERVER)/`basename $(NEWLIBDIST)`
NEWLIBSRC	= newlib-$(NEWLIBVER)
NEWLIBBLD	= build/newlib-$(NEWLIBVER)
LIBCPDFURL	= $(NEWLIBSERVER)/libc.pdf
LIBMPDFURL	= $(NEWLIBSERVER)/libm.pdf
LIBCPDF		= $(TEMP)/libc.pdf
LIBMPDF		= $(TEMP)/libm.pdf

GDBVER		= 7.5.1
GDBSERVER	= http://ftp.gnu.org/gnu/gdb
GDBDIST		= $(TEMP)/gdb-$(GDBVER).tar.bz2
GDBURL		= $(GDBSERVER)/`basename $(GDBDIST)`
GDBSRC		= gdb-$(GDBVER)
GDBBLD		= build/gdb-$(GDBVER)

VERSION		= $(BINUTILVER)_$(GCCVER)_$(NEWLIBVER)_$(GDBVER)
RELEASE		= 1

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
TARBALL		= $(PKGNAME)-$(VERSION)-$(shell uname -o)-$(shell uname -m).tgz
else
TARBALL		= $(PKGNAME)-$(VERSION)-$(shell uname -s)-$(shell uname -m).tgz
endif

ifeq ($(shell uname), OpenBSD)
GCCEXTRACONFIG	+= --with-gmp=/usr/local
GCCEXTRACONFIG	+= --with-mpc=/usr/local
GCCEXTRACONFIG	+= --with-mpfr=/usr/local
PACKAGENAME	= $(PKGNAME)-$(VERSION).tgz
endif

default: readme.done

################################################################################

# Download all source distributions

download: $(BINUTILDIST) $(GCCDIST) $(NEWLIBDIST) $(GDBDIST) $(LIBCPDF) $(LIBMPDF)

################################################################################

# Unpack all source distributions

source.done: $(BINUTILDIST) $(GCCDIST) $(NEWLIBDIST) $(GDBDIST) $(LIBCPDF) $(LIBMPDF)
	$(TAR) xzf $(BINUTILDIST)
	$(TAR) xjf $(GCCDIST)
	if [ -f multilibs.$(ABI).patch ]; then cd $(GCCSRC) ; patch -b -p0 <../multilibs.$(ABI).patch ; fi
ifeq ($(shell uname), OpenBSD)
	cd $(GCCSRC) ; patch -b -p0 <../openbsd.pch.patch
endif
	$(TAR) xzf $(NEWLIBDIST)
	ln -s "../$(NEWLIBSRC)/newlib" $(GCCSRC)/newlib
	$(TAR) xjf $(GDBDIST)
	touch $@

################################################################################

# Download binutils

$(BINUTILDIST):
	wget -nv -P $(TEMP) $(BINUTILURL)

# Compile binutils

binutils.done: source.done
	rm -rf $(BINUTILBLD)
	mkdir -p $(BINUTILBLD)
	cd $(BINUTILBLD) && ../../$(BINUTILSRC)/configure --prefix=$(INSTBASE) --target=$(TARGETNAME) --enable-interwork --enable-multilib --enable-lto --disable-nls --disable-shared --with-float=soft --disable-werror
	$(MAKE) $(MAKEJOBS) -C $(BINUTILBLD)
	$(MAKE) -C $(BINUTILBLD) install
	touch binutils.done

################################################################################

# Download gcc

$(GCCDIST):
	wget -nv -P $(TEMP) $(GCCURL)

# Compile gcc

gcc.done: binutils.done
	rm -rf $(GCCBLD)
	mkdir -p $(GCCBLD)
	cd $(GCCBLD) && ../../$(GCCSRC)/configure --prefix=$(INSTBASE) --target=$(TARGETNAME) --enable-interwork --enable-multilib --enable-lto --disable-nls --disable-shared --with-float=soft --disable-werror --enable-languages=c,c++ --disable-libssp --disable-libgomp --with-newlib --disable-libgloss --disable-newlib-supplied-syscalls $(GCCEXTRACONFIG)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) $(MAKEJOBS) -C $(GCCBLD)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCBLD) install
	touch gcc.done

################################################################################

# Download newlib

$(NEWLIBDIST):
	wget -nv -P $(TEMP) $(NEWLIBURL)

# Note: newlib is built by gcc

# Download newlib docs

$(LIBCPDF): 
	wget -nv -P $(TEMP) $(LIBCPDFURL)

$(LIBMPDF):
	wget -nv -P $(TEMP) $(LIBMPDFURL)

# Install newlib docs

newlibdocs.done: $(LIBCPDF) $(LIBMPDF)
	mkdir -p $(INSTBASE)/doc
	install -cm 0444 $(LIBCPDF) $(INSTBASE)/doc
	install -cm 0444 $(LIBMPDF) $(INSTBASE)/doc
	touch newlibdocs.done

################################################################################

# Download gdb

$(GDBDIST):
	wget -nv -P $(TEMP) $(GDBURL)

# Compile gdb

gdb.done: $(GDBDIST)
	test -f /usr/include/expat.h
	rm -rf $(GDBBLD)
	mkdir -p $(GDBBLD)
	cd $(GDBBLD) && ../../$(GDBSRC)/configure --prefix=$(INSTBASE) --target=$(TARGETNAME) --enable-interwork --enable-multilib --disable-libssp --disable-nls --disable-shared --disable-werror
	$(MAKE) $(MAKEJOBS) -C $(GDBBLD)
	$(MAKE) -C $(GDBBLD) install
	touch gdb.done

################################################################################

# Create README.txt

readme.done: binutils.done gcc.done newlibdocs.done gdb.done
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
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	$(TAR) czf $(TARBALL) `basename $(INSTBASE)` --mode=ugo-w
else
	$(TAR) czf $(TARBALL) `basename $(INSTBASE)` --owner=root --group=root --mode=ugo-w
endif

################################################################################

# Create Linux RPM package

ifeq ($(shell uname), Linux)
fakeroot: readme.done
	mkdir -p fakeroot/usr/local
	cp -R -p $(PKGNAME) fakeroot/usr/local

specfile: specfile.template fakeroot
	sed s/@@PKGNAME@@/$(PKGNAME)/g <specfile.template | sed s/@@VERSION@@/$(VERSION)/g | sed s/@@RELEASE@@/$(RELEASE)/g >specfile
	$(FIND) fakeroot/usr/local/$(PKGNAME) -type d | awk '{ printf("%%dir /%s\n", substr($$1, 10)); }' >>specfile
	$(FIND) fakeroot/usr/local/$(PKGNAME) -type f | cut -c 9- >>specfile
	$(FIND) fakeroot/usr/local/$(PKGNAME) -type l | cut -c 9- >>specfile

rpm: specfile
	rpmbuild --buildroot=`pwd`/fakeroot --define="_topdir `pwd`/rpmbuild" -bb specfile
	cp rpmbuild/RPMS/*/*.rpm .
endif

################################################################################

# Create OpenBSD package

ifeq ($(shell uname), OpenBSD)

fakeroot: readme.done
	mkdir -p fakeroot/usr/local
	cp -R -p $(PKGNAME) fakeroot/usr/local
# Why aren't these links already created on OpenBSD?
	ln -s liblto_plugin.so.0.0 fakeroot/usr/local/$(PKGNAME)/libexec/gcc/arm-none-eabi/$(GCCVER)/liblto_plugin.so
	ln -s liblto_plugin.so.0.0 fakeroot/usr/local/$(PKGNAME)/libexec/gcc/arm-none-eabi/$(GCCVER)/liblto_plugin.so.0

CONTENTS: fakeroot
	echo "@owner root"				>CONTENTS
	echo "@group wheel"				>>CONTENTS
	echo "@mode -w"					>>CONTENTS
	echo "@cwd /usr/local"				>>CONTENTS
	find fakeroot/usr/local/$(PKGNAME) -type d | awk '{ printf("@dir %s\n", substr($$1, 20)); }' >>CONTENTS
	find fakeroot -type f | cut -c 20- | sort	>>CONTENTS
	find fakeroot -type l | awk '{ printf("echo %s `readlink %s`\n", $$1, $$1); }' | sh | \
	awk '{ printf("@exec ln -s %s %s\n", $$2, substr($$1,9)); }'            >>CONTENTS
	find fakeroot -type l | awk '{ printf("@unexec rm %s\n", substr($$1, 9)); }' >>CONTENTS

COMMENT:
	echo "ARM Microcontroller Toolchain"		>COMMENT

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
	rm -rf build fakeroot specfile rpmbuild *.done *.rpm *.tgz

distclean: clean
