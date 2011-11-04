# Makefile for building and installing stlink-download

# $Id$

HOSTCC		?= gcc
CFLAGS		?= -Wall

PROGRAM		= stlink-download
DESTDIR		?= /usr/local/bin

UDEVRULES	= 10-stlink.rules
UDEVRULESDIR	?= /etc/udev/rules.d

default: $(PROGRAM)

stlink-download: stlink-download.c
	$(HOSTCC) $(CFLAGS) -o $@ $<

install: $(PROGRAM)
	install -csm 0555 $(PROGRAM)		$(DESTDIR)
	install -cm 0444 ../udev/$(UDEVRULES)	$(UDEVRULESDIR)

uninstall:
	rm $(DESTDIR)/$(PROGRAM)
	rm $(UDEVRULESDIR)/$(UDEVRULES)

clean:
	-rm $(PROGRAM)
