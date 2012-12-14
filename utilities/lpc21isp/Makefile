# Makefile for building LPC21ISP RPM package

# $Id: Makefile 2963 2011-08-02 17:06:09Z svn $

CC		= $(CROSS_COMPILE)gcc

LPC21ISP_NAME	= lpc21isp
LPC21ISP_VER	= 1.85
LPC21ISP_ZIP	= $(LPC21ISP_NAME)_$(shell echo $(LPC21ISP_VER) | awk -F '.' '{ printf("%s%s\n", $$1, $$2) }').zip
LPC21ISP_SERVER	= http://downloads.sourceforge.net/project/lpc21isp/lpc21isp/$(LPC21ISP_VER)
LPC21ISP_URL	= $(LPC21ISP_SERVER)/$(LPC21ISP_ZIP)
LPC21ISP_DIR	= $(LPC21ISP_NAME)_$(shell echo $(LPC21ISP_VER) | awk -F '.' '{ printf("%s%s\n", $$1, $$2) }')
LPC21ISP_PROG	= $(LPC21ISP_NAME)

INSTALLDIR	= /usr/local/bin

TAR		= tar

.PHONY: default install uninstall clean reallyclean distclean

default: $(LPC21ISP_PROG)

# Download lpc21isp source distribution

$(LPC21ISP_ZIP):
	wget -O $(LPC21ISP_ZIP) $(LPC21ISP_URL)

# Unpack lpc21isp source distribution

$(LPC21ISP_DIR): $(LPC21ISP_ZIP)
	mkdir -p $(LPC21ISP_DIR)
	unzip $(LPC21ISP_ZIP) -d $(LPC21ISP_DIR)

# Compile lpc21isp

$(LPC21ISP_PROG): $(LPC21ISP_DIR)
	$(MAKE) -C $(LPC21ISP_DIR) CC=$(CC)
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

distclean: reallyclean
	-rm $(LPC21ISP_DIST)
	-rm $(LPC21ISP_ZIP)
