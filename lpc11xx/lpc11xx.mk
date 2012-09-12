# Processor dependent make definitions

# $Id$

MCU		= $(MCUFAMILY)

CPUFLAGS	+= -mcpu=cortex-m0 -mthumb -DCORTEX_M0
FLASHWRITEADDR	?= 0x00000000
TEXTBASE	?= 0x00000000

CFLAGS		+= -DLPC11XX
LDFLAGS		+= -Ttext $(TEXTBASE)

# Board specific macro definitions

ifeq ($(BOARDNAME), LPC1114FN28)
BOARDFLAGS	?= -DCONSOLE_PORT='"com1:115200,n,8,1"'
MCU		= LPC1114FN28
endif

# Phony targets

.PHONY:		lib clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU)

# Build processor dependent support library

include $(MCUDIR)/CMSIS/CMSIS.mk

LIBOBJS		= cpu.o serial.o

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	$(MAKE) cmsis
	$(MAKE) otherlibs

lib: lib$(MCU).a

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
