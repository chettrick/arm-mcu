# Make processor dependent startup and libraries for STR91x

# $Id: Makefile,v 1.2 2008-01-15 10:31:55 cvs Exp $

ARMSRC	= ..

ARCH	= arm9
MCU	= str912faw44

# Build support library

lib$(MCU).a: crt0.o conio.o cpu.o syscalls.o
	$(AR) crs lib$(MCU).a conio.o
	$(AR) crs lib$(MCU).a cpu.o
	$(AR) crs lib$(MCU).a syscalls.o

include $(ARMSRC)/include/ARM.mk
