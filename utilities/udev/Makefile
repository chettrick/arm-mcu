# Makefile for installing udev rules for ARM microcontroller programmers

# $Id$

UDEVRULESDIR	= /etc/udev/rules.d

install:
	for F in *.rules ; do install -cm 0444 $$F $(UDEVRULESDIR) ; done

uninstall:
	for F in *.rules ; do rm $(UDEVRULESDIR)/$$F ; done
