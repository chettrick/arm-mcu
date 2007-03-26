# Make processor dependent startup and libraries for LPC2366

# $Id: Makefile,v 1.1 2007-03-26 18:33:25 cvs Exp $

ARMSRC	= ..
MCU	= lpc2366

# Build support library

lib$(MCU).a: crt0.o conio.o syscalls.o
	$(AR) crs lib$(MCU).a conio.o
	$(AR) crs lib$(MCU).a syscalls.o

include $(ARMSRC)/ARM.mk
