# Make processor dependent startup and libraries for AT91SAM7S256

# $Id: Makefile,v 1.1 2008-01-09 21:04:06 cvs Exp $

ARMSRC	= ..

ARCH	= arm7tdmi        
MCU	= at91sam7s256

# Build support library

lib$(MCU).a: crt0.o cpu.o syscalls.o
	$(AR) crs lib$(MCU).a cpu.o
	$(AR) crs lib$(MCU).a syscalls.o

include $(ARMSRC)/include/ARM.mk
