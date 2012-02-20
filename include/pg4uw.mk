# Make definitions for BK Precision Universal Device Programmer

# $Id$

PG4UWCMD	?= pg4uwcmd.exe
PG4UWPRJ	?= $(MCU).eprj

.SUFFIXES: .flashpg4uw

# Program flash with pg4uw

.hex.flashpg4uw:
	$(PG4UWCMD) /Prj:$(PG4UWPRJ) /Loadfile:$^ /Program:noanyquest /Close
