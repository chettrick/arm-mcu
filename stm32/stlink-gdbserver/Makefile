# Makefile for building GDB server for STM32 ST-Link

# $Id$

STLINKURL	= git://github.com/whitequark/stlink.git
STLINKSRC	= stlink
STLINKGDB	= stlink-gdbserver

INSTALLDIR	= /usr/local/bin

default: $(STLINKGDB)

$(STLINKSRC):
	git clone $(STLINKURL) $(STLINKSRC)
	cd $(STLINKSRC) ; patch -p0 <../gdbserver.patch

$(STLINKGDB): $(STLINKSRC)
	$(MAKE) -C $(STLINKSRC)
	cp $(STLINKSRC)/gdbserver/st-util		$(STLINKGDB)

install:
	install -csm 0555 $(STLINKGDB)			$(INSTALLDIR)

clean:
	-rm $(STLINKGDB)
	$(MAKE) -C $(STLINKSRC) clean

reallyclean: clean

distclean: reallyclean
	-rm -rf $(STLINKSRC)
