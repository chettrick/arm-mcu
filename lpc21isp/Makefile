# Makefile for building LPC21ISP RPM package

# $Id$

LPC21ISP_NAME	= lpc21isp
LPC21ISP_VER	= 1.64
LPC21ISP_DIR	= $(LPC21ISP_NAME)-$(LPC21ISP_VER)
LPC21ISP_DIST	= $(LPC21ISP_DIR).tar.gz
LPC21ISP_PROG	= $(LPC21ISP_DIR)/$(LPC21ISP_NAME)
LPC21ISP_SERVER	= http://sourceforge.net/projects/$(LPC21ISP_NAME)/files/$(LPC21ISP_NAME)
LPC21ISP_URL	= $(LPC21ISP_SERVER)/$(LPC21ISP_DIST)
LPC21ISP_DEST	= `pwd`/fakeroot/usr/local/bin

.PHONY: default rpm clean distclean

ifeq ($(shell uname), Linux)
default: rpm
else
default: $(LPC21ISP_PROG)
endif

$(LPC21ISP_DIST):
	wget -nd $(LPC21ISP_URL)

$(LPC21ISP_DIR): $(LPC21ISP_DIST)
	tar xzf $(LPC21ISP_DIST)

$(LPC21ISP_PROG): $(LPC21ISP_DIR)
	$(MAKE) -C $(LPC21ISP_DIR) clean all
	cp $(LPC21ISP_PROG) .

$(LPC21ISP_DEST): $(LPC21ISP_PROG)
	mkdir -p $(LPC21ISP_DEST)
	install -csm 0555 $(LPC21ISP_PROG) $(LPC21ISP_DEST)

specfile: specfile.template
	sed s/@@VERSION@@/$(LPC21ISP_VER)/g <specfile.template >specfile

rpm: specfile $(LPC21ISP_DEST)
	mkdir -p rpmbuild/RPMS/$(MACHTYPE)
	rpmbuild --buildroot=`pwd`/fakeroot --define="_topdir `pwd`/rpmbuild" -bb specfile
	cp rpmbuild/RPMS/$(MACHTYPE)/*.rpm .

clean:
	-rm -rf $(LPC21ISP_DIR)
	-rm -rf $(LPC21ISP_DEST)
	-rm -rf fakeroot
	-rm -rf rpmbuild
	-rm specfile
	-rm *.rpm

distclean: clean
	-rm $(LPC21ISP_DIST)
