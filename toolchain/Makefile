# Download and build GNU toolchain for ARM microcontrollers

# $Id$

PKGNAME		= arm-tools
INSTBASE	= $(shell pwd)/$(PKGNAME)
TEMP		= /tmp
TARGETNAME	= arm-elf
MACHTYPE	= $(shell uname -i)

BINUTILVER	= 2.21
BINUTILSERVER	= http://ftp.gnu.org/pub/gnu/binutils
BINUTILDIST	= $(TEMP)/binutils-$(BINUTILVER).tar.gz
BINUTILURL	= $(BINUTILSERVER)/`basename $(BINUTILDIST)`
BINUTILSRC	= binutils-$(BINUTILVER)
BINUTILOBJ	= binutils-$(BINUTILVER).obj

GCCVER		= 4.5.2
GCCSERVER	= http://ftp.gnu.org/pub/gnu/gcc/gcc-$(GCCVER)
GCCDIST		= $(TEMP)/gcc-$(GCCVER).tar.bz2
GCCURL		= $(GCCSERVER)/`basename $(GCCDIST)`
GCCSRC		= gcc-$(GCCVER)
GCCOBJ		= gcc-$(GCCVER).obj

NEWLIBVER	= 1.19.0
NEWLIBSERVER	= http://mirrors.kernel.org/sources.redhat.com/newlib
NEWLIBDIST	= $(TEMP)/newlib-$(NEWLIBVER).tar.gz
NEWLIBURL	= $(NEWLIBSERVER)/`basename $(NEWLIBDIST)`
NEWLIBSRC	= newlib-$(NEWLIBVER)
LIBCPDFURL	= $(NEWLIBSERVER)/libc.pdf
LIBMPDFURL	= $(NEWLIBSERVER)/libm.pdf
LIBCPDF		= $(TEMP)/libc.pdf
LIBMPDF		= $(TEMP)/libm.pdf

GDBVER		= 7.2
GDBSERVER	= http://ftp.gnu.org/gnu/gdb
GDBDIST		= $(TEMP)/gdb-$(GDBVER).tar.bz2
GDBURL		= $(GDBSERVER)/`basename $(GDBDIST)`
GDBSRC		= gdb-$(GDBVER)
GDBOBJ		= gdb-$(GDBVER).obj

VERSION		= $(BINUTILVER)_$(GCCVER)_$(NEWLIBVER)_$(GDBVER)
RELEASE		= 1

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
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

source.done: $(BINUTILDIST) $(GCCDIST) $(NEWLIBDIST) $(GDBDIST) $(LIBCPDF) $(LIBMPDF)
	tar xzf $(BINUTILDIST)
	tar xjf $(GCCDIST)
	tar xzf $(NEWLIBDIST)
	tar xjf $(GDBDIST)
	touch $@

################################################################################

# Download binutils

$(BINUTILDIST):
	wget -P $(TEMP) $(BINUTILURL)

# Compile binutils

binutils.done: source.done
	rm -rf $(BINUTILOBJ)
	mkdir -p $(BINUTILOBJ)
	cd $(BINUTILOBJ) && ../$(BINUTILSRC)/configure --prefix=$(INSTBASE) --target=$(TARGETNAME) --enable-interwork --enable-multilib --disable-nls --disable-shared --with-float=soft --disable-werror
	$(MAKE) -C $(BINUTILOBJ)
	$(MAKE) -C $(BINUTILOBJ) install
	touch binutils.done

################################################################################

# Download gcc

$(GCCDIST):
	wget -P $(TEMP) $(GCCURL)

# Compile gcc

gcc.done: binutils.done
	rm -rf $(GCCOBJ)
	mkdir -p $(GCCOBJ)
	cd $(GCCOBJ) && ../$(GCCSRC)/configure --prefix=$(INSTBASE) --target=$(TARGETNAME) --enable-interwork --enable-multilib --enable-languages=c --disable-libssp --disable-libgomp --disable-nls --disable-shared --with-newlib --with-float=soft --disable-werror $(GCCEXTRACONFIG)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCOBJ)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCOBJ) install
	touch gcc.done

################################################################################

# Download newlib

$(NEWLIBDIST):
	wget -P $(TEMP) $(NEWLIBURL)

# Compile newlib

newlib.done: gcc.done
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
	rm -rf $(GDBOBJ)
	mkdir -p $(GDBOBJ)
	cd $(GDBOBJ) && ../$(GDBSRC)/configure --prefix=$(INSTBASE) --target=$(TARGETNAME) --enable-interwork --enable-multilib --disable-libssp --disable-nls --disable-shared --disable-werror
	$(MAKE) -C $(GDBOBJ)
	$(MAKE) -C $(GDBOBJ) install
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
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	tar czf $(TARBALL) `basename $(INSTBASE)` --mode=ugo-w
else
	tar czf $(TARBALL) `basename $(INSTBASE)` --owner=root --group=root --mode=ugo-w
endif

################################################################################

# Create toolchain RPM package

fakeroot: readme.done
	mkdir -p fakeroot/usr/local
	cp -R -p arm-tools fakeroot/usr/local

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
	rm -rf $(NEWLIBSRC)
	rm -rf $(GDBSRC)
	rm -rf *.obj fakeroot specfile rpmbuild *.rpm

distclean: clean
