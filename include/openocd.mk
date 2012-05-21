# Make definitions for OpenOCD

# $Id$

OPENOCD		?= openocd
OPENOCDCFG	?= $(MCUDIR)/$(MCU).openocd
OPENOCDDEBUG	?= $(ARMSRC)/common/main.gdb
OPENOCDFLASH	?= $(MCUDIR)/$(MCU).flashocd
OPENOCDIF	?= olimex-jtag-tiny

.PHONY: startocd stopocd
.SUFFIXES: .debugocd .flashocd

# Start OpenOCD

startocd:
	$(OPENOCD) -f interface/$(OPENOCDIF).cfg -f $(OPENOCDCFG) >debug.log 2>&1 &

# Stop OpenOCD

stopocd:
	-skill `basename $(OPENOCD) .exe`

# Debug with OpenOCD

.elf.debugocd:
	$(MAKE) startocd
	$(GDBGUI) $(GDB) $(GDBFLAGS) -x $(OPENOCDDEBUG) $<
	$(MAKE) stopocd

# Program flash with OpenOCD

.bin.flashocd:
	$(MAKE) startocd
	$(OPENOCDFLASH) $< $(FLASHWRITEADDR) $(TEXTBASE)
	$(MAKE) stopocd
