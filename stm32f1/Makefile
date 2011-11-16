# Make processor dependent startup and libraries

# $Id$

ARMSRC		= ..
MCUFAMILY	= stm32f1
BOARDNAME	?= OLIMEX_STM32_P107

ifeq ($(BOARDNAME), OLIMEX_STM32_P103)
MCU             = stm32f103rb
endif

ifeq ($(BOARDNAME), OLIMEX_STM32_P107)
MCU             = stm32f107rb
endif

ifeq ($(BOARDNAME), STM32_VALUE_LINE_DISCOVERY)
MCU             = stm32f100rb
endif

ifeq ($(BOARDNAME), W5200E01_M3)
MCU             = stm32f103c8
endif

default: lib$(MCU).a

include $(ARMSRC)/include/ARM.mk
