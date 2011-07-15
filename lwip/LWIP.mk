# ARM LWIP make definitions

# $Id$

LWIP_DIR	?= $(ARMSRC)/lwip
LWIP_VERSION	= 1.3.2
LWIP_SRC	= $(LWIP_DIR)/lwip-$(LWIP_VERSION)/src
LWIP_INC	= $(LWIP_SRC)/include
CFLAGS		+= -I$(LWIP_DIR) -I$(LWIP_INC) -I$(LWIP_INC)/ipv4

.PHONY: lwip_lib lwip_clean

LWIP_OBJS	= $(LWIP_SRC)/core/mem.o		\
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
		  $(LWIP_SRC)/core/dhcp.o		\
		  $(LWIP_SRC)/core/init.o		\
		  $(LWIP_SRC)/core/ipv4/autoip.o	\
		  $(LWIP_SRC)/core/ipv4/icmp.o		\
		  $(LWIP_SRC)/core/ipv4/ip.o		\
		  $(LWIP_SRC)/core/ipv4/inet.o		\
		  $(LWIP_SRC)/core/ipv4/ip_addr.o	\
		  $(LWIP_SRC)/core/ipv4/ip_frag.o	\
		  $(LWIP_SRC)/core/ipv4/inet_chksum.o	\
		  $(LWIP_SRC)/netif/etharp.o		\

# Add LWIP object files to the MCU library

lwip_lib: $(LWIP_OBJS)
	$(AR) crs lib$(MCU).a $(LWIP_OBJS)

# Remove LWIP object files

lwip_clean:
	rm -f $(LWIP_OBJS)
