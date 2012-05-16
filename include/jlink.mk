# Make definitions for J-Link

# $Id$

JLINKEXE	?= JLinkExe
JLINKFLASHCMDS	= jlinkflash.tmp
JLINKMCU	= $(MCU)
JLINKDEBUG	?= $(MCUDIR)/$(MCU).debugjlink
JLINKGDB	?= JLinkGDBServer
JLINKGDBIF	?= -if JTAG
JLINKGDBOPTS	?= -port $(GDBSERVERPORT)

.PHONY: startjlink stopjlink
.SUFFIXES: .debugjlink .flashjlink

# Start J-Link GDB server

startjlink:
	$(JLINKGDB) $(JLINKGDBIF) $(JLINKGDBOPTS) >debug.log 2>&1 &

# Stop J-Link GDB server

stopjlink:
	skill `basename $(JLINKGDB) .exe`

# Debug with J-Link

.elf.debugjlink:
	$(MAKE) startjlink
	$(GDBGUI) $(GDB) $(GDBFLAGS) -x $(JLINKDEBUG) $<
	$(MAKE) stopjlink

# Flash with J-Link

.bin.flashjlink:
	@echo "exec device=$(JLINKMCU)"			>$(JLINKFLASHCMDS)
	@echo "h"					>>$(JLINKFLASHCMDS)
	@echo "loadbin $<, 0x`dc -e '16o 16i $(subst 0x,,$(FLASHWRITEADDR)) $(subst 0x,,$(TEXTBASE)) + p'`"	>>$(JLINKFLASHCMDS)
	@echo "r"					>>$(JLINKFLASHCMDS)
	@echo "g"					>>$(JLINKFLASHCMDS)
	@echo "exit"					>>$(JLINKFLASHCMDS)
	-$(JLINKEXE) $(JLINKFLASHCMDS)
	@rm $(JLINKFLASHCMDS)
	@rm Default.ini
