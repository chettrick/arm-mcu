# Make processor dependent startup and libraries for LPC2119

# $Id: Makefile,v 1.6 2007-10-10 03:24:05 cvs Exp $

ARMSRC	= ..
MCU	= lpc2119

# Build support library

lib$(MCU).a: crt0.o conio.o cpu.o syscalls.o
	$(AR) crs lib$(MCU).a conio.o
	$(AR) crs lib$(MCU).a cpu.o
	$(AR) crs lib$(MCU).a syscalls.o

include $(ARMSRC)/include/ARM.mk
