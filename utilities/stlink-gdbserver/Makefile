# Makefile for building GDB server for STM32 ST-Link

# $Id$

STLINKURL	= git://github.com/whitequark/stlink.git
STLINKSRC	= stlink
STLINKGDB	= stlink-gdbserver
STLINKFLASH	= stlink-flash

INSTALLDIR	= /usr/local/bin

UDEVRULES	= 10-stlink.rules
UDEVRULESDIR	?= /etc/udev/rules.d

default: $(STLINKGDB)

$(STLINKSRC):
	git clone $(STLINKURL) $(STLINKSRC)
	cd $(STLINKSRC) ; patch -p0 <../gdbserver.patch

$(STLINKGDB): $(STLINKSRC)
	$(MAKE) -C $(STLINKSRC)
	cp $(STLINKSRC)/gdbserver/st-util		$(STLINKGDB)
	cp $(STLINKSRC)/flash/flash			$(STLINKFLASH)

install:
	install -csm 0555 $(STLINKGDB)			$(INSTALLDIR)
	install -csm 0555 $(STLINKFLASH)		$(INSTALLDIR)
	install -cm 0444 ../udev/$(UDEVRULES)		$(UDEVRULESDIR)

uninstall:
	-rm $(INSTALLDIR)/$(STLINKGDB)
	-rm $(INSTALLDIR)/$(STLINKFLASH)
	-rm $(UDEVRULESDIR)/$(UDEVRULES)

clean:
	-rm $(STLINKGDB)
	-rm $(STLINKFLASH)
	$(MAKE) -C $(STLINKSRC) clean

reallyclean: clean

distclean: reallyclean
	-rm -rf $(STLINKSRC)
