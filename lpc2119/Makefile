# Make processor dependent startup and libraries for LPC2119

# $Id: Makefile,v 1.8 2007-12-20 13:22:19 cvs Exp $

ARMSRC	= ..

ARCH	= arm7tdmi-s
MCU	= lpc2119

# Build support library

lib$(MCU).a: crt0.o conio.o cpu.o syscalls.o
	$(AR) crs lib$(MCU).a conio.o
	$(AR) crs lib$(MCU).a cpu.o
	$(AR) crs lib$(MCU).a syscalls.o

include $(ARMSRC)/include/ARM.mk
