# Makefile for simple hello world application

# $Id$

# Override the following macro to move the framework directory

ARMSRC	?= ..

# Override the following macro to build for another MCU

MCU		?= lpc23xx
MCUFAMILY	?= lpc23xx

# The following targets are of interest:

# make hello.hex
# make hello.bin
# make hello.asm
# make hello.flashisp
# make hello.flashocd
# make hello.debug
# make clean

default: hello.hex

include $(ARMSRC)/include/ARM.mk
