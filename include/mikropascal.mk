# Makefile definition Mikropascal ARM microcontroller programming

# $Id$

MIKROPASCAL	?= "C:/Users/Public/Documents/Mikroelektronika/mikroPascal PRO for ARM/mPARM.exe"

.PHONY: mikropascal_clean

.SUFFIXES: .build .mppar

# Build project

.mppar.build:
	$(MIKROPASCAL) -RA -BIN -PF $<

# Clean out working files

mikropascal_clean:
	-rm -f *.bmk
	-rm -f *.brk
	-rm -f *.dbg
	-rm -f *.dct
	-rm -f *.dlt
	-rm -f *.emcl
	-rm -f *.hex
	-rm -f *.lst
	-rm -f *callertable.txt
	-rm -f *.mpas.ini
	-rm -f *.user.dic
