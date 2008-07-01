# Make processor dependent startup and libraries for LPC2119

# $Id: Makefile,v 1.10 2008-07-01 18:12:00 cvs Exp $

ARMSRC		= ..

ARCH		= arm7tdmi-s
MCU		= lpc2119

LIBOBJS		= conio.o cpu.o syscalls.o

# Build support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)

# Remove working files

clean_$(MCU):
	-rm *.a *.o

include $(ARMSRC)/include/ARM.mk
