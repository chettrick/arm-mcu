# Make definitions for mbed

# $Id$

# mbed firmware directory

MBEDDIR		?= /media/MBED

.SUFFIXES: .flashmbed

# Install firmware to mbed firmware directory

.bin.flashmbed:
	test -d $(MBEDDIR) -a -w $(MBEDDIR)
	cp $< $(MBEDDIR)
	sync
	@echo -e "\nPress RESET on the target board to start $<\n"
