# Makefile for building GDB server for STM32 ST-Link

# $Id$

STLINKURL	= git://github.com/texane/stlink.git
STLINKSRC	= stlink
STLINKGDB	= stlink-gdbserver
STLINKFLASH	= stlink-flash

INSTALLDIR	= /usr/local/bin

default: $(STLINKGDB)

# Download stlink-gdbserver source distribution

$(STLINKSRC):
	git clone --depth 1 $(STLINKURL) $(STLINKSRC)
	-awk '/\+\+\+/ { printf("cp %s %s.original\n", $$2, $$2); }' *.patch | sh
	-for P in *.patch ; do patch -p0 <$$P ; done

# Compile stlink-gdbserver

$(STLINKGDB): $(STLINKSRC)
	$(MAKE) -C $(STLINKSRC)
	cp $(STLINKSRC)/gdbserver/st-util		$(STLINKGDB)
	cp $(STLINKSRC)/flash/flash			$(STLINKFLASH)

# Install stlink-gdbserver

install:
	install -csm 0555 $(STLINKGDB)			$(INSTALLDIR)
	install -csm 0555 $(STLINKFLASH)		$(INSTALLDIR)

# Uninstall stlink-gdbserver

uninstall:
	-rm $(INSTALLDIR)/$(STLINKGDB)
	-rm $(INSTALLDIR)/$(STLINKFLASH)

# Clean out working files

clean:
	-rm $(STLINKGDB)
	-rm $(STLINKFLASH)
	$(MAKE) -C $(STLINKSRC) clean

reallyclean: clean

distclean: reallyclean
	-rm -rf $(STLINKSRC)
