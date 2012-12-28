# Makefile for installing udev rules for ARM microcontroller programmers

# $Id$

UDEVRULESDIR	= /etc/udev/rules.d
LIBEXECDIR	= /usr/local/libexec

install:
	for F in *.rules ; do install -cm 0444 $$F $(UDEVRULESDIR) ; done
	for F in *.helper ; do install -cm 0555 $$F $(LIBEXECDIR) ; done

uninstall:
	for F in *.rules ; do rm $(UDEVRULESDIR)/$$F ; done
	for F in *.helper ; do rm $(LIBEXECDIR)/$$F ; done
