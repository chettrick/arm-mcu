# Makefile for installing udev rules for ARM microcontroller programmers

# $Id$

RULESDIR	= /etc/udev/rules.d

install:
	for F in *.rules ; do install -cm 0444 $$F $(RULESDIR) ; done

uninstall:
	for F in *.rules ; do rm $(RULESDIR)/$$F ; done
