# ARM WizNet driver make definitions

# $Id$

WIZNET_DIR	?= $(ARMSRC)/wiznet
WIZNET_DEVICE	?= W5200

CFLAGS		+= -DWIZNET -I$(WIZNET_DIR)

ifeq ($(WIZNET_DEVICE), W5100)
CFLAGS		+= -DW5100
endif

ifeq ($(WIZNET_DEVICE), W5200)
CFLAGS		+= -DW5200
endif

.PHONY: wiznet_lib wiznet_clean

WIZNET_OBJS	= $(WIZNET_DIR)/W5200.o

# Add WizNet object files to the MCU library

wiznet_lib: $(WIZNET_OBJS)
	$(AR) crs lib$(MCU).a $(WIZNET_OBJS)

# Remove WizNet object files

wiznet_clean:
	rm -f $(WIZNET_OBJS)
