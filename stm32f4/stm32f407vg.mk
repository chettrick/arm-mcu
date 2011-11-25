# Processor dependent make definitions

# $Id$

ifeq ($(BOARDNAME), STM32F4_DISCOVERY)
CFLAGS		+= -DHSE_VALUE=8000000
endif

include stm32f4.mk
