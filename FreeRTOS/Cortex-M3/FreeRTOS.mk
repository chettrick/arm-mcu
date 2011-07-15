# FreeRTOS make definitions

# $Id$

CFLAGS		+= -DFREERTOS -I$(FREERTOS)

.PHONY: freertos_lib freertos_clean

# These are the FreeRTOS object files

FREERTOS_OBJS	= $(FREERTOS)/croutine.o	\
		  $(FREERTOS)/heap_3.o		\
		  $(FREERTOS)/list.o		\
		  $(FREERTOS)/port.o		\
		  $(FREERTOS)/queue.o		\
		  $(FREERTOS)/tasks.o		\
		  $(FREERTOS)/timers.o

# Add FreeRTOS object files to the MCU library

freertos_lib: $(FREERTOS_OBJS)
	$(AR) crs lib$(MCU).a $(FREERTOS_OBJS)

# Remove FreeRTOS object files

freertos_clean:
	rm -f $(FREERTOS_OBJS)
