# Make processor dependent startup and libraries

# $Id$

ARMSRC		?= ..
MCUFAMILY	= stm32f1
#BOARDNAME	?= OLIMEX_STM32_P103
BOARDNAME	?= OLIMEX_STM32_P107
#BOARDNAME	?= STM32_VALUE_LINE_DISCOVERY
#BOARDNAME	?= W5200E01_M3

include $(ARMSRC)/include/ARM.mk

.PHONY: clean reallyclean distclean

clean: ARM_mk_clean

reallyclean: clean

distclean: reallyclean
