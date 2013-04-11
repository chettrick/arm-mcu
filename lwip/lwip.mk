# ARM LWIP make definitions

# $Id$

# Copyright (C)2013, Philip Munts, President, Munts AM Corp.
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

LWIP_VERSION	= 1.3.2
LWIP_SRC	= $(LWIP_DIR)/lwip-$(LWIP_VERSION)/src
LWIP_INC	= $(LWIP_SRC)/include

CFLAGS		+= -DLWIP -I$(LWIP_DIR) -I$(LWIP_INC) -I$(LWIP_INC)/ipv4
RMAKEFLAGS	+= WITH_LWIP=$(WITH_LWIP)

.PHONY: lwip_lib lwip_clean

LWIP_OBJS	= $(LWIP_SRC)/core/dhcp.o		\
		  $(LWIP_SRC)/core/init.o		\
		  $(LWIP_SRC)/core/ipv4/autoip.o	\
		  $(LWIP_SRC)/core/ipv4/icmp.o		\
		  $(LWIP_SRC)/core/ipv4/inet.o		\
		  $(LWIP_SRC)/core/ipv4/inet_chksum.o	\
		  $(LWIP_SRC)/core/ipv4/ip.o		\
		  $(LWIP_SRC)/core/ipv4/ip_addr.o	\
		  $(LWIP_SRC)/core/ipv4/ip_frag.o	\
		  $(LWIP_SRC)/core/mem.o		\
		  $(LWIP_SRC)/core/memp.o		\
		  $(LWIP_SRC)/core/netif.o		\
		  $(LWIP_SRC)/core/pbuf.o		\
		  $(LWIP_SRC)/core/raw.o		\
		  $(LWIP_SRC)/core/stats.o		\
		  $(LWIP_SRC)/core/sys.o		\
		  $(LWIP_SRC)/core/tcp.o		\
		  $(LWIP_SRC)/core/tcp_in.o		\
		  $(LWIP_SRC)/core/tcp_out.o		\
		  $(LWIP_SRC)/core/udp.o		\
		  $(LWIP_SRC)/netif/etharp.o		\

# Add LWIP object files to the MCU library

lwip_lib: $(LWIP_OBJS)
	$(AR) crs lib$(MCU).a $(LWIP_OBJS)

# Remove LWIP object files

lwip_clean:
	rm -f $(LWIP_OBJS)

# Add to target lists

LIBTARGETS	+= lwip_lib
CLEANTARGETS	+= lwip_clean
