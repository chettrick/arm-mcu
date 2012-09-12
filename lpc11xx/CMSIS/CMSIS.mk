# Makefile for LPC17xx CMSIS library

# $Id$

CMSISDIR	= $(MCUDIR)/CMSIS
CMSISINC	= $(CMSISDIR)/inc
CMSISSRC	= $(CMSISDIR)/src

CFLAGS		+= -I$(CMSISDIR)/inc

.PHONY: cmsis

cmsis:
	for F in $(CMSISSRC)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(FIND) $(CMSISSRC) -type f -name '*.o' -exec $(AR) crs lib$(MCU).a {} ";"
