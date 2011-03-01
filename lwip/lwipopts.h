/* LWIP options for ARM microcomputer */

// $Id$

#ifndef __ARCH_LWIPOPTS_H__
#define __ARCH_LWIPOPTS_H__

#include <stdlib.h>

#define NO_SYS			1

#define MEM_LIBC_MALLOC		1
#define MEM_ALIGNMENT		4
#define MEM_SIZE		16384

#define LWIP_ARP		1
#define LWIP_ICMP		1
#define LWIP_DHCP		1
#define LWIP_AUTOIP		1
#define LWIP_RAW		1
#define LWIP_CHKSUM_ALGORITHM	2

#define LWIP_NETCONN		0
#define LWIP_SOCKET		0
#define LWIP_STATS		0
#define LWIP_STATS_DISPLAY	0

#define ETHARP_TRUST_IP_MAC	0
#define ETH_PAD_SIZE		2

#define mem_init()
#define mem_free		free
#define mem_malloc		malloc
#define mem_calloc		calloc
#define mem_realloc		realloc

#endif /* __ARCH_LWIPOPTS_H__ */
