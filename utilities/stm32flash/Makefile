# Makefile for stm32flash flash programming utility

# $Id$

STM32FLASH_NAME		= stm32flash
STM32FLASH_SERVER	= http://stm32flash.googlecode.com/files
STM32FLASH_DIST		= $(STM32FLASH_NAME).tar.gz
STM32FLASH_URL		= $(STM32FLASH_SERVER)/$(STM32FLASH_DIST)
STM32FLASH_DIR		= $(STM32FLASH_NAME).src
STM32FLASH_PROG		= $(STM32FLASH_NAME)

INSTALLDIR		= /usr/local/bin

TAR			= tar

.PHONY: default install clean reallyclean distclean

default: $(STM32FLASH_PROG)

# Download stm32flash source distribution

$(STM32FLASH_DIST):
	wget -O $(STM32FLASH_DIST) $(STM32FLASH_URL)

# Unpack stm32flash source distribution

$(STM32FLASH_DIR): $(STM32FLASH_DIST)
	$(TAR) xzf $(STM32FLASH_DIST)
	mv $(STM32FLASH_NAME) $(STM32FLASH_DIR)
	cd $(STM32FLASH_DIR) ; patch -p0 <../cygwin.patch

# Compile stm32flash

$(STM32FLASH_PROG): $(STM32FLASH_DIR)
	$(MAKE) -C $(STM32FLASH_DIR)
	cp $(STM32FLASH_DIR)/$(STM32FLASH_PROG) $(STM32FLASH_PROG)

# Install stm32flash

install: $(STM32FLASH_PROG)
	install -csm 0555 $(STM32FLASH_PROG) $(INSTALLDIR)

# Uninstall stm32flash

uninstall:
	-rm $(INSTALLDIR)/$(STM32FLASH_PROG)

# Clean out working files

clean:
	-rm $(STM32FLASH_PROG)

reallyclean: clean
	-rm -rf $(STM32FLASH_DIR)

distclean: reallyclean
	-rm $(STM32FLASH_DIST)
