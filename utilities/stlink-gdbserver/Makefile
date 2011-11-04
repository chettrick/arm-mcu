# Makefile for building GDB server for STM32 ST-Link

# $Id$

STLINKURL	= git://github.com/whitequark/stlink.git
STLINKSRC	= stlink
STLINKGDB	= stlink-gdbserver
STLINKFLASH	= stlink-flash

INSTALLDIR	= /usr/local/bin

UDEVRULES	= 50-stlink.rules
UDEVRULESDIR	?= /etc/udev/rules.d

default: $(STLINKGDB)

# Download stlink-gdbserver source distribution

$(STLINKSRC):
	git clone $(STLINKURL) $(STLINKSRC)
	cd $(STLINKSRC) ; patch -p0 <../gdbserver.patch

# Compile stlink-gdbserver

$(STLINKGDB): $(STLINKSRC)
	$(MAKE) -C $(STLINKSRC)
	cp $(STLINKSRC)/gdbserver/st-util		$(STLINKGDB)
	cp $(STLINKSRC)/flash/flash			$(STLINKFLASH)

# Install stlink-gdbserver

install:
	install -csm 0555 $(STLINKGDB)			$(INSTALLDIR)
	install -csm 0555 $(STLINKFLASH)		$(INSTALLDIR)
	install -cm 0444 ../udev/$(UDEVRULES)		$(UDEVRULESDIR)

# Uninstall stlink-gdbserver

uninstall:
	-rm $(INSTALLDIR)/$(STLINKGDB)
	-rm $(INSTALLDIR)/$(STLINKFLASH)
	-rm $(UDEVRULESDIR)/$(UDEVRULES)

# Clean out working files

clean:
	-rm $(STLINKGDB)
	-rm $(STLINKFLASH)
	$(MAKE) -C $(STLINKSRC) clean

reallyclean: clean

distclean: reallyclean
	-rm -rf $(STLINKSRC)
