/* WizNet W5100 Register Definitions */

// $Id$

#ifndef _W5100_H
#define _W5100_H

#include <_ansi.h>
#include <stdint.h>

#define MAX_SOCKETS		4

// Common Registers

#define	W5100_MR		0x0000
#define W5100_GAR		0x0001
#define W5100_SUBR		0x0005
#define W5100_SHAR		0x0009
#define W5100_SIPR		0x000F
#define W5100_IR		0x0015
#define W5100_IMR		0x0016
#define W5100_RTR		0x0017
#define W5100_RCR		0x0019
#define W5100_RMSR		0x001A
#define W5100_TMSR		0x001B
#define W5100_PATR		0x001C
#define W5100_PTIMER		0x0028
#define W5100_PMAGIC		0x0029
#define W5100_UIPR		0x002A
#define W5100_UPORT		0x002E

// Socket Registers

#define W5100_SOCKET_REG(s)	(0x0400 + (s << 8))

#define W5100_Sn_MR(s)		(W5100_SOCKET_REG(s) + 0x00)
#define W5100_Sn_CR(s)		(W5100_SOCKET_REG(s) + 0x01)
#define W5100_Sn_IR(s)		(W5100_SOCKET_REG(s) + 0x02)
#define W5100_Sn_SR(s)		(W5100_SOCKET_REG(s) + 0x03)
#define W5100_Sn_PORT(s)	(W5100_SOCKET_REG(s) + 0x04)
#define W5100_Sn_DHAR(s)	(W5100_SOCKET_REG(s) + 0x06)
#define W5100_Sn_DIPR(s)	(W5100_SOCKET_REG(s) + 0x0C)
#define W5100_Sn_DPORT(s)	(W5100_SOCKET_REG(s) + 0x10
#define W5100_Sn_MSSR(s)	(W5100_SOCKET_REG(s) + 0x12)
#define W5100_Sn_PROTO(s)	(W5100_SOCKET_REG(s) + 0x14)
#define W5100_Sn_IP_TOS(s)	(W5100_SOCKET_REG(s) + 0x15)
#define W5100_Sn_IP_TTL(s)	(W5100_SOCKET_REG(s) + 0x16)
#define W5100_Sn_TX_FSR(s)	(W5100_SOCKET_REG(s) + 0x20)
#define W5100_Sn_TX_RD(s)	(W5100_SOCKET_REG(s) + 0x22)
#define W5100_Sn_TX_WR(s)	(W5100_SOCKET_REG(s) + 0x24)
#define W5100_Sn_RX_RSR(s)	(W5100_SOCKET_REG(s) + 0x26)
#define W5100_Sn_RX_RD(s)	(W5100_SOCKET_REG(s) + 0x28)

// W5100 register bit masks

#define W5100_MR_RST		0x80
#define W5100_MR_PB		0x10
#define W5100_MR_PPPOE_ENABLE	0x08

#define W5100_IR_CONFLICT	0x80
#define W5100_IR_UNREACH	0x40
#define W5100_IR_PPPOE_CLOSE	0x20

#define W5100_IMR_CONFLICT	0x80
#define W5100_IMR_UNREACH	0x40
#define W5100_IMR_PPPOE_CLOSE	0x20

// W5100 specific driver functions

_BEGIN_STD_C

int W5100_write_register(const uint16_t address, const uint8_t data);

int W5100_read_register(const uint16_t address, uint8_t *data);

_END_STD_C
#endif
