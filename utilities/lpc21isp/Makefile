# Makefile for building LPC21ISP RPM package

# $Id: Makefile 2963 2011-08-02 17:06:09Z svn $

LPC21ISP_NAME	= lpc21isp
LPC21ISP_VER	= 1.84
LPC21ISP_DIST	= $(LPC21ISP_NAME)_$(shell echo $(LPC21ISP_VER) | awk -F '.' '{ printf("%s%s\n", $$1, $$2) }').tar.gz
LPC21ISP_ZIP	= $(LPC21ISP_NAME)_$(shell echo $(LPC21ISP_VER) | awk -F '.' '{ printf("%s%s\n", $$1, $$2) }').zip
LPC21ISP_SERVER	= http://downloads.sourceforge.net/project/lpc21isp/lpc21isp/1.83
LPC21ISP_URL	= $(LPC21ISP_SERVER)/$(LPC21ISP_DIST)
LPC21ISP_DIR	= $(LPC21ISP_NAME)_$(shell echo $(LPC21ISP_VER) | awk -F '.' '{ printf("%s%s\n", $$1, $$2) }')
LPC21ISP_PROG	= $(LPC21ISP_NAME)

INSTALLDIR	= /usr/local/bin

TAR		= tar

.PHONY: default zip2tgz install clean distclean

default: $(LPC21ISP_PROG)

# Convert zip distribution (from Yahoo Groups) to tarball distribution

zip2tgz: $(LPC21ISP_ZIP)
	mkdir zz
	unzip $(LPC21ISP_ZIP) -d zz
	cd zz ; tar czf ../$(LPC21ISP_DIST) *
	rm -rf zz

# Download lpc21isp source distribution

$(LPC21ISP_DIST):
	wget -O $(LPC21ISP_DIST) $(LPC21ISP_URL)

# Unpack lpc21isp source distribution

$(LPC21ISP_DIR): $(LPC21ISP_DIST)
	mkdir -p $(LPC21ISP_DIR)
	$(TAR) xzf $(LPC21ISP_DIST) --directory=$(LPC21ISP_DIR)

# Compile lpc21isp

$(LPC21ISP_PROG): $(LPC21ISP_DIR)
	$(MAKE) -C $(LPC21ISP_DIR) CFLAGS=-Dstrnicmp=strncasecmp clean all
	cp $(LPC21ISP_DIR)/$(LPC21ISP_PROG) $(LPC21ISP_PROG)

# Install lpc21isp

install: $(LPC21ISP_PROG)
	install -csm 0555 $(LPC21ISP_PROG) $(INSTALLDIR)

# Uninstall lpc21isp

uninstall:
	-rm $(INSTALLDIR)/$(LPC21ISP_PROG)

# Install lpc21isp to fakeroot

fakeroot: $(LPC21ISP_PROG)
	mkdir -p fakeroot/$(INSTALLDIR)
	install -csm 0555 $(LPC21ISP_PROG) fakeroot/$(INSTALLDIR)

# Create RPM spec file

specfile: fakeroot specfile.template
	sed s#@@VERSION@@#$(LPC21ISP_VER)#g <specfile.template >specfile

rpm: specfile
	rpmbuild --buildroot=`pwd`/fakeroot --define="_topdir `pwd`/rpmbuild" -bb specfile
	cp rpmbuild/RPMS/*/*.rpm .

# Clean out working files

clean:
	-$(MAKE) -C $(LPC21ISP_DIR) clean
	-rm -rf $(LPC21ISP_PROG)
	-rm -rf fakeroot
	-rm -rf rpmbuild
	-rm *.rpm
	-rm specfile

reallyclean: clean
	-rm -rf $(LPC21ISP_DIR)

distclean: clean
	-rm $(LPC21ISP_DIST)
