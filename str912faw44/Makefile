# Make processor dependent startup and libraries for STR91x

# $Id: Makefile,v 1.7 2008-07-01 18:12:00 cvs Exp $

ARMSRC		= ..

ARCH		= arm9
MCU		= str912faw44

FWLIB		= $(MCUDEPENDENT)/FWLib
LIBOBJS		= conio.o cpu.o syscalls.o

CFLAGS		+= -I$(FWLIB)

# Build support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(FWLIB)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(FWLIB)/*.o

# Clean out working files

clean_$(MCU):
	rm -f *.a *.o $(FWLIB)/*.o

include $(ARMSRC)/include/ARM.mk
