# Makefile for building LPC21ISP RPM package

# $Id$

LPC21ISP_NAME	= lpc21isp
LPC21ISP_DIR	= $(LPC21ISP_NAME)
LPC21ISP_DIST	= $(LPC21ISP_DIR).tar.gz
ifeq ($(shell uname), CYGWIN_NT-5.1)
LPC21ISP_PROG	= $(LPC21ISP_DIR)/$(LPC21ISP_NAME).exe
else
LPC21ISP_PROG	= $(LPC21ISP_DIR)/$(LPC21ISP_NAME)
endif
LPC21ISP_URL	= http://lpc21isp.svn.sourceforge.net/viewvc/lpc21isp.tar.gz?view=tar
LPC21ISP_DEST	= `pwd`/fakeroot/usr/local/bin
LPC21ISP_VER	= `awk '/define.*VERSION_STR/ { print substr($$3, 2, length($$3)-2); }' < $(LPC21ISP_DIR)/lpc21isp.c`

.PHONY: default prog rpm clean distclean

ifeq ($(shell uname), Linux)
default: rpm
else
default: prog
endif

$(LPC21ISP_DIST):
	wget -O $(LPC21ISP_DIST) -nd $(LPC21ISP_URL)

$(LPC21ISP_DIR): $(LPC21ISP_DIST)
	tar xzf $(LPC21ISP_DIST)

$(LPC21ISP_PROG): $(LPC21ISP_DIR)
	$(MAKE) -C $(LPC21ISP_DIR) CFLAGS=-Dstrnicmp=strncasecmp clean all

prog: $(LPC21ISP_PROG)

$(LPC21ISP_DEST): $(LPC21ISP_PROG)
	mkdir -p $(LPC21ISP_DEST)
	install -csm 0555 $(LPC21ISP_PROG) $(LPC21ISP_DEST)

specfile: specfile.template $(LPC21ISP_PROG)
	sed s#@@VERSION@@#$(LPC21ISP_VER)#g <specfile.template >specfile

rpm: specfile $(LPC21ISP_DEST)
	mkdir -p rpmbuild/RPMS/$(MACHTYPE)
	rpmbuild --buildroot=`pwd`/fakeroot --define="_topdir `pwd`/rpmbuild" -bb specfile
	cp rpmbuild/RPMS/$(MACHTYPE)/*.rpm .

clean:
	-rm -rf $(LPC21ISP_PROG)
	-rm -rf $(LPC21ISP_DIR)
	-rm -rf $(LPC21ISP_DEST)
	-rm -rf fakeroot
	-rm -rf rpmbuild
	-rm specfile
	-rm *.rpm

reallyclean: clean

distclean: clean
	-rm $(LPC21ISP_DIST)
