# Make processor dependent startup and libraries for LPC2119

# $Id: Makefile,v 1.2 2007-02-07 22:46:09 cvs Exp $

ARMSRC	= ..
MCU	= lpc2119

lpc2119: crt0.o libmunts.a

# Build support library

libmunts.a: conio.o syscalls.o
	$(AR) crs libmunts.a conio.o
	$(AR) crs libmunts.a syscalls.o

include ../ARM.mk
include flash.mk
