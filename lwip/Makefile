# Makefile for simple hello world application

# $Id$

# Override the following macro to move the framework directory

ARMSRC		?= ..

# Override the following macro to build for another MCU

MCU		?= lpc2366

# LWIP source directories

LWIP_DIR	= $(ARMSRC)/lwip
LWIP_VERSION	= 1.3.2
LWIP_SRC	= $(LWIP_DIR)/lwip-$(LWIP_VERSION)/src

# LWIP object files

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
		  $(LWIP_SRC)/netif/etharp.o

# Build LWIP include path

CFLAGS		+= -I$(LWIP_DIR) -I$(LWIP_SRC)/include -I$(LWIP_SRC)/include/ipv4

default: liblwip.a

# Build LWIP library

liblwip.a: $(LWIP_OBJS)
	$(AR) crs liblwip.a $(LWIP_OBJS)

include $(ARMSRC)/include/ARM.mk
