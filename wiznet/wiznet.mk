# ARM WizNet driver make definitions

# $Id$

WIZNET_DIR	?= $(ARMSRC)/wiznet
CFLAGS		+= -DWIZNET -I$(WIZNET_DIR)

.PHONY: wiznet_lib wiznet_clean

ifeq ($(WITH_W5100),yes)
WIZNET_OBJS	+= $(WIZNET_DIR)/W5100.o
endif

ifeq ($(WITH_W5200),yes)
WIZNET_OBJS	+= $(WIZNET_DIR)/W5200.o
endif

# Add WizNet object files to the MCU library

wiznet_lib: $(WIZNET_OBJS)
	$(AR) crs lib$(MCU).a $(WIZNET_OBJS)

# Remove WizNet object files

wiznet_clean:
	rm -f $(WIZNET_OBJS)
