# Make processor dependent startup and libraries for LPC2366

# $Id: Makefile,v 1.3 2007-10-10 02:28:53 cvs Exp $

ARMSRC	= ..
MCU	= lpc2366

# Build support library

lib$(MCU).a: crt0.o conio.o cpu.o syscalls.o
	$(AR) crs lib$(MCU).a conio.o
	$(AR) crs lib$(MCU).a cpu.o
	$(AR) crs lib$(MCU).a syscalls.o

include $(ARMSRC)/include/ARM.mk
