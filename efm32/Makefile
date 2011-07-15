# Make processor dependent startup and libraries

# $Id$

ARMSRC		= ..
MCUFAMILY	= efm32
BOARDNAME	?= EFM32_G8XX_STK

ifeq ($(BOARDNAME), EFM32_G8XX_STK)
MCU		= EFM32G890F128
endif

default: lib$(MCU).a

include $(ARMSRC)/include/ARM.mk
