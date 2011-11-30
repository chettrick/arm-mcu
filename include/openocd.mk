# Make definitions for OpenOCD

# $Id$

OPENOCD		?= openocd
OPENOCDCFG	?= $(MCUDIR)/$(MCU).openocd
OPENOCDDEBUG	?= $(ARMSRC)/common/main.gdb
OPENOCDFLASH	?= $(MCUDIR)/$(MCU).flashocd
OPENOCDIF	?= olimex-jtag-tiny

.PHONY: startocd stopocd
.SUFFIXES: .debugocd .flashocd

# Debug with OpenOCD

.elf.debugocd:
	$(GDBGUI) $(GDB) $(GDBFLAGS) -x $(OPENOCDDEBUG) $<

# Program flash with OpenOCD

.bin.flashocd:
	$(MAKE) startocd
	$(OPENOCDFLASH) $< $(FLASHWRITEADDR) $(TEXTBASE)
	$(MAKE) stopocd

# Start OpenOCD

startocd:
	$(OPENOCD) -f interface/$(OPENOCDIF).cfg -f $(OPENOCDCFG) >debug.log 2>&1 &

# Stop OpenOCD

stopocd:
	skill `basename $(OPENOCD) .exe`