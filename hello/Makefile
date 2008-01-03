# Makefile for simple hello world application

# $Id: Makefile,v 1.1 2008-01-03 10:37:57 cvs Exp $

# Override the following macro to move the framework directory

ARMSRC	?= ..

# Override the following macros to use on another MCU

ARCH	?= arm7tdmi-s
MCU	?= lpc2366

# The following targets are of interest:

# make hello.hex
# make hello.bin
# make hello.asm
# make hello.flashisp
# make hello.flashocd
# make hello.debug
# make clean
# make resetocd

default: hello.hex

include $(ARMSRC)/include/ARM.mk
