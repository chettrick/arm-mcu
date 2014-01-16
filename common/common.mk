# Common library make definitions

# $Id$

# Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

CFLAGS		+= -I$(COMMON_DIR)

.PHONY: common_lib common_clean

COMMON_OBJS	=  $(COMMON_DIR)/conio.o
COMMON_OBJS	+= $(COMMON_DIR)/device.o
COMMON_OBJS	+= $(COMMON_DIR)/inet.o
COMMON_OBJS	+= $(COMMON_DIR)/msrand32.o
COMMON_OBJS	+= $(COMMON_DIR)/semihosting.o
COMMON_OBJS	+= $(COMMON_DIR)/syscalls.o

# Add common object files to the MCU library

common_lib: $(COMMON_OBJS)
	$(AR) crs lib$(MCU).a $(COMMON_OBJS)

# Remove common object files

common_clean:
	rm -f $(COMMON_OBJS)

# Add to target lists

LIBTARGETS	+= common_lib
CLEANTARGETS	+= common_clean
