# FreeRTOS make definitions

# $Id$

CFLAGS		+= -DFREERTOS -I$(FREERTOS_DIR)

.PHONY: freertos_lib freertos_clean

# These are the FreeRTOS object files

FREERTOS_OBJS	= $(FREERTOS_DIR)/croutine.o		\
		  $(FREERTOS_DIR)/heap_3.o		\
		  $(FREERTOS_DIR)/list.o		\
		  $(FREERTOS_DIR)/port.o		\
		  $(FREERTOS_DIR)/queue.o		\
		  $(FREERTOS_DIR)/tasks.o		\
		  $(FREERTOS_DIR)/timers.o

# Add FreeRTOS object files to the MCU library

freertos_lib: $(FREERTOS_OBJS)
	$(AR) crs lib$(MCU).a $(FREERTOS_OBJS)

# Remove FreeRTOS object files

freertos_clean:
	rm -f $(FREERTOS_OBJS)
