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
	$(MAKE) startocd
	$(GDBGUI) $(GDB) $(GDBFLAGS) -x $(OPENOCDDEBUG) $<
	$(MAKE) stopocd

# Program flash with OpenOCD

.bin.flashocd:
	$(MAKE) startocd
	$(OPENOCDFLASH) $< $(FLASHWRITEADDR) $(TEXTBASE)

# Start OpenOCD

startocd:
	$(OPENOCD) -f interface/$(OPENOCDIF).cfg -f $(OPENOCDCFG) >debug.log 2>&1 &
	tcpwait localhost $(GDBSERVERPORT) 10

# Stop OpenOCD

stopocd:
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	killall `basename $(OPENOCD) .exe`
else
	killall $(OPENOCD)
endif
