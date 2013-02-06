/* WizNet Driver Functions */

// $Id$

// Copyright (C)2013, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// * Neither the name of Munts AM Corp. nor the names of its contributors may
//   be used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

static const char revision[] = "$Id$";

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
