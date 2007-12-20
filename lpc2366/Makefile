# Make processor dependent startup and libraries for LPC2366

# $Id: Makefile,v 1.5 2007-12-20 13:23:57 cvs Exp $

ARMSRC	= ..

ARCH	= arm7tdmi-s
MCU	= lpc2366

# Build support library

lib$(MCU).a: crt0.o conio.o cpu.o syscalls.o
	$(AR) crs lib$(MCU).a conio.o
	$(AR) crs lib$(MCU).a cpu.o
	$(AR) crs lib$(MCU).a syscalls.o

include $(ARMSRC)/include/ARM.mk
