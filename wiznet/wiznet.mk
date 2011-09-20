# ARM WizNet driver make definitions

# $Id$

WIZNET_DIR	?= $(ARMSRC)/wiznet
CFLAGS		+= -I$(WIZNET_DIR)

.PHONY: wiznet_lib wiznet_clean

WIZNET_OBJS	= $(WIZNET_DIR)/W5200.o

# Add WizNet object files to the MCU library

wiznet_lib: $(WIZNET_OBJS)
	$(AR) crs lib$(MCU).a $(WIZNET_OBJS)

# Remove WizNet object files

wiznet_clean:
	rm -f $(WIZNET_OBJS)
