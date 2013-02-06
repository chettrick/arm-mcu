/* WizNet Driver Function Prototypes */

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

#ifndef _WIZNET_H
#define _WIZNET_H

#include <_ansi.h>
#include <stddef.h>
#include <stdint.h>

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

_BEGIN_STD_C

typedef uint8_t macaddress_t[6];		// Ethernet MAC address

typedef uint8_t ipv4address_t[4];		// IPv4 address

void wiznet_tick(void);

int wiznet_initialize(const uint32_t spiportnum,
                      const uint32_t numsockets);

int wiznet_set_hardware_address(const macaddress_t address);

int wiznet_get_hardware_address(macaddress_t address);

int wiznet_configure_network(const ipv4address_t address,
                             const ipv4address_t subnet,
                             const ipv4address_t gateway);

int wiznet_get_ipaddress(ipv4address_t address);

int wiznet_get_linkstate(uint32_t *linkstate);

int wiznet_get_port(const uint32_t socket,
                    uint32_t *port);

int wiznet_get_receive_ready(const uint32_t socket,
                             size_t *count);

int wiznet_get_transmit_free(const uint32_t socket,
                             size_t *count);

int wiznet_udp_open(const uint32_t socket,
                    const uint16_t port);

int wiznet_udp_receive_from(const uint32_t socket,
                            ipv4address_t srcaddr,
                            uint16_t *srcport,
                            uint8_t *buf,
                            size_t *count);

int wiznet_udp_send_to(const uint32_t socket,
                       const ipv4address_t destaddr,
                       const uint32_t destport,
                       uint8_t *buf,
                       const uint32_t count);

int wiznet_bootp(ipv4address_t address,
                 ipv4address_t subnet,
                 ipv4address_t gateway,
                 ipv4address_t nameserver);

_END_STD_C
#endif
