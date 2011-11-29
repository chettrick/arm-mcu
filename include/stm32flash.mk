# Make definitions for the stm32flash utility

# $Id$

STM32FLASH	?= stm32flash
STM32FLASH_PORT	?= /dev/ttyS0

.SUFFIXES: .stm32flash

# Program flash with stm32flash and serial boot loader

.bin.stm32flash:
	$(STM32FLASH) -w $< -v -g 0x0 $(STM32FLASH_PORT)
