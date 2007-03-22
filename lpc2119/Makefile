# Make processor dependent startup and libraries for LPC2119

# $Id: Makefile,v 1.4 2007-03-22 20:58:55 cvs Exp $

ARMSRC	= ..
MCU	= lpc2119

# Build support library

lib$(MCU).a: crt0.o conio.o syscalls.o
	$(AR) crs lib$(MCU).a conio.o
	$(AR) crs lib$(MCU).a syscalls.o

include $(ARMSRC)/ARM.mk
