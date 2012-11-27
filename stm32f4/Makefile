# Make processor dependent startup and libraries

# $Id: Makefile 2983 2011-08-31 11:51:13Z svn $
 
ARMSRC		?= ..
MCUFAMILY	= stm32f4
BOARDNAME	?= STM32F4_DISCOVERY
#BOARDNAME	?= FEZ_CERB40

include $(ARMSRC)/include/ARM.mk

.PHONY: clean reallyclean distclean

clean: ARM_mk_clean

reallyclean: clean

distclean: reallyclean
