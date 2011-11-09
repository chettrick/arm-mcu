# Makefile for building and installing stlink-v1-flash

# $Id$

HOSTCC		?= gcc
CFLAGS		?= -Wall

PROGRAM		= stlink-v1-flash
INSTALLDIR	?= /usr/local/bin

default: $(PROGRAM)

# Compile stlink-v1-flash

stlink-v1-flash: stlink-v1-flash.c
	$(HOSTCC) $(CFLAGS) -o $@ $<

# Install stlink-v1-flash

install: $(PROGRAM)
	install -csm 0555 $(PROGRAM)		$(INSTALLDIR)

# Uninstall stlink-v1-flash

uninstall:
	rm $(INSTALLDIR)/$(PROGRAM)

# Clean out working files

clean:
	-rm $(PROGRAM)

reallyclean: clean

distclean: reallyclean
