# Makefile for building and installing stlink-download

# $Id$

HOSTCC		?= gcc
CFLAGS		?= -Wall

PROGRAM		= stlink-download
RULES		= 10-stlink.rules

DESTDIR		?= /usr/local/bin
UDEVRULES	?= /etc/udev/rules.d

default: $(PROGRAM)

stlink-download: stlink-download.c
	$(HOSTCC) $(CFLAGS) -o $@ $<

install: $(PROGRAM)
	install -csm 04555 $(PROGRAM)	$(DESTDIR)
	install -cm 0444 $(RULES)	$(UDEVRULES)

uninstall:
	rm $(DESTDIR)/$(PROGRAM)
	rm $(UDEVRULES)/$(RULES)

clean:
	-rm $(PROGRAM)
