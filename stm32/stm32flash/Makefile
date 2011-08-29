#Makefile for stm32flash flash programming utility

# $Id$

STM32FLASH_NAME		= stm32flash
STM32FLASH_SERVER	= http://stm32flash.googlecode.com/files
STM32FLASH_DIST		= $(STM32FLASH_NAME).tar.gz
STM32FLASH_URL		= $(STM32FLASH_SERVER)/$(STM32FLASH_DIST)
STM32FLASH_DIR		= $(STM32FLASH_NAME)
STM32FLASH_PROG		= $(STM32FLASH_DIR)/$(STM32FLASH_NAME)
STM32FLASH_DEST		= /usr/local/bin

TAR			= tar

.PHONY: default install clean reallyclean distclean

default: $(STM32FLASH_PROG)

# Download source distribution

$(STM32FLASH_DIST):
	wget -O $(STM32FLASH_DIST) $(STM32FLASH_URL)

# Unpack source distribution

$(STM32FLASH_DIR): $(STM32FLASH_DIST)
	$(TAR) xzf $(STM32FLASH_DIST)

# Compile

$(STM32FLASH_PROG): $(STM32FLASH_DIR)
	$(MAKE) -C $(STM32FLASH_DIR)

# Install

install: $(STM32FLASH_PROG)
	install -csm 0555 $(STM32FLASH_PROG) $(STM32FLASH_DEST)

# Clean out working files

clean:
	-rm $(STM32FLASH_PROG)

reallyclean: clean
	-rm -rf $(STM32FLASH_DIR)

distclean: reallyclean
	-rm $(STM32FLASH_DIST)
