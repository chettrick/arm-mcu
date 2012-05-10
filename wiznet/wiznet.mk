# ARM WizNet driver make definitions

# $Id$

WIZNET_DIR	?= $(ARMSRC)/wiznet
CFLAGS		+= -DWIZNET -I$(WIZNET_DIR)

.PHONY: wiznet_lib wiznet_clean

# Device independent object files

WIZNET_OBJS	+= $(WIZNET_DIR)/wiznet.o

# Device dependent object files

ifeq ($(WITH_W5200),yes)
CFLAGS		+= -DW5200
WIZNET_OBJS	+= $(WIZNET_DIR)/W5200.o
endif

# Add WizNet object files to the MCU library

wiznet_lib: $(WIZNET_OBJS)
	$(AR) crs lib$(MCU).a $(WIZNET_OBJS)

# Remove WizNet object files

wiznet_clean:
	rm -f $(WIZNET_OBJS)
