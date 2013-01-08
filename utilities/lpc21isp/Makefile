# Makefile for building LPC21ISP RPM package

# $Id: Makefile 2963 2011-08-02 17:06:09Z svn $

LPC21ISP_NAME	= lpc21isp
LPC21ISP_URL	= https://github.com/capiman/lpc21isp.git
LPC21ISP_DIR	= lpc21isp.src
LPC21ISP_VER	= $(shell awk '/define VERSION_STR/ { print $$3 }' $(LPC21ISP_DIR)/lpc21isp.c)
LPC21ISP_PROG	= $(LPC21ISP_NAME)

CC		= $(CROSS_COMPILE)gcc

INSTALLDIR	= /usr/local/bin

.PHONY: default install uninstall clean reallyclean distclean

default: $(LPC21ISP_PROG)

# Fetch lpc21isp source tree

$(LPC21ISP_DIR):
	git clone $(LPC21ISP_URL) $(LPC21ISP_DIR)

# Compile lpc21isp

$(LPC21ISP_PROG): $(LPC21ISP_DIR)
	echo VERSION is $(LPC21ISP_VER)
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
