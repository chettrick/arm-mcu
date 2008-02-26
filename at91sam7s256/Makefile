# Make processor dependent startup and libraries for AT91SAM7S256

# $Id: Makefile,v 1.3 2008-02-26 12:36:04 cvs Exp $

ARMSRC		= ..

ARCH		= arm7tdmi        
MCU		= at91sam7s256

LIBOBJS		= conio.o cpu.o syscalls.o

# Build support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)

include $(ARMSRC)/include/ARM.mk
