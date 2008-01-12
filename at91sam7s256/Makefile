# Make processor dependent startup and libraries for AT91SAM7S256

# $Id: Makefile,v 1.2 2008-01-12 21:23:06 cvs Exp $

ARMSRC	= ..

ARCH	= arm7tdmi        
MCU	= at91sam7s256

# Build support library

lib$(MCU).a: crt0.o conio.o cpu.o syscalls.o
	$(AR) crs lib$(MCU).a conio.o
	$(AR) crs lib$(MCU).a cpu.o
	$(AR) crs lib$(MCU).a syscalls.o

include $(ARMSRC)/include/ARM.mk
