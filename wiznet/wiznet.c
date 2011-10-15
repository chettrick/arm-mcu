/* WizNet Driver Functions */

// $Id$

#include <errno.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiznet.h>

#define errno_r (*(__errno()))

typedef struct
{
  uint8_t op;
  uint8_t htype;
  uint8_t hlen;
  uint8_t hops;
  uint32_t xid;
  uint16_t secs;
  uint16_t flags;
  ipv4address_t ciaddr;
  ipv4address_t yiaddr;
  ipv4address_t siaddr;
  ipv4address_t giaddr;
  uint8_t chaddr[16];
  char sname[64];
  char file[128];
  uint8_t vend[64];
} __attribute__((packed)) bootp_message_t;

static const ipv4address_t broadcast_address = { 255, 255, 255, 255 };
static const ipv4address_t zero_address	= { 0, 0, 0, 0 };

volatile uint32_t wiznet_delaycounter = 0;

void wiznet_tick(void)
{
  if (wiznet_delaycounter)
    wiznet_delaycounter--;
}
