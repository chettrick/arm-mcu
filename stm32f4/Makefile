# Make processor dependent startup and libraries

# $Id: Makefile 2983 2011-08-31 11:51:13Z svn $

ARMSRC		= ..
MCUFAMILY	= stm32f4
BOARDNAME	?= STM32F4_DISCOVERY

ifeq ($(BOARDNAME), STM32F4_DISCOVERY)
MCU             = stm32f407vg
endif

default: lib$(MCU).a

include $(ARMSRC)/include/ARM.mk
