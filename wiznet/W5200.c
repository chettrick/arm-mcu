/* W5200 Device Driver */

// $Id$

// Copyright (C)2013, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification,are permitted provided that the following conditions are met:
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

#include <cpu.h>
#include <errno.h>
#include <inet.h>
#include <socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiznet.h>
#include <W5200.h>

static uint32_t spiport = 0;
static uint32_t numsockets = 0;
static uint16_t addressmask = 0;

/* This table abstracts the W5200 RAM size configuration for 1 to 8 sockets. */
/* We divide available RAM equally amoung the number of configured sockets.  */
/* We don't try to give unequal amounts of RAM to different sockets.         */

static const struct
{
  uint32_t SIZE;
  uint32_t CONFIG;
} RAMSIZE_TABLE[W5200_MAX_SOCKETS+1] =
{
  { 0,			0				},
// Does not work => { W5200_RAMSIZE,	W5200_RAMSIZE_CONFIG_WHOLE	},
  { W5200_RAMSIZE/2,	W5200_RAMSIZE_CONFIG_HALF	},
  { W5200_RAMSIZE/2,	W5200_RAMSIZE_CONFIG_HALF	},
  { W5200_RAMSIZE/4,	W5200_RAMSIZE_CONFIG_QUARTER	},
  { W5200_RAMSIZE/4,	W5200_RAMSIZE_CONFIG_QUARTER	},
  { W5200_RAMSIZE/8,	W5200_RAMSIZE_CONFIG_EIGHTH	},
  { W5200_RAMSIZE/8,	W5200_RAMSIZE_CONFIG_EIGHTH	},
  { W5200_RAMSIZE/8,	W5200_RAMSIZE_CONFIG_EIGHTH	},
  { W5200_RAMSIZE/8,	W5200_RAMSIZE_CONFIG_EIGHTH	},
};

/* This table holds precalculated TX and RX RAM base addresses for */
/* each socket.                                                    */

static struct
{
  uint32_t TX_RAM_base;
  uint32_t RX_RAM_base;
} socket_table[W5200_MAX_SOCKETS];

int W5200_write_register(const uint16_t address,
                         const uint8_t data)
{
  uint8_t cmdbuf[5];

  cmdbuf[0] = (address >> 8) & 0xFF;
  cmdbuf[1] = address & 0xFF;
  cmdbuf[2] = 0x80;
  cmdbuf[3] = 0x01;
  cmdbuf[4] = data;

  return spi_master_transfer(spiport, cmdbuf, 5, NULL, 0);
}

int W5200_read_register(const uint16_t address,
                        uint8_t *data)
{
  uint8_t cmdbuf[4];

  cmdbuf[0] = (address >> 8) & 0xFF;
  cmdbuf[1] = address & 0xFF;
  cmdbuf[2] = 0x00;
  cmdbuf[3] = 0x01;

  return spi_master_transfer(spiport, cmdbuf, 4, data, 1);
}

int W5200_read_receive_ram(const uint32_t socket,
                           const uint16_t rampointer,
                           uint8_t *buf,
                           const size_t count)
{
  int status = 0;
  uint16_t srcmask;
  uint16_t srcaddr;
  uint16_t maxbeforewrap;
  uint8_t cmdbuf[4];
  
  // Validate parameters

  if (socket >= numsockets)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if (buf == NULL)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if (count == 0)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  srcmask = rampointer & addressmask;
  srcaddr = socket_table[socket].RX_RAM_base + srcmask;

  maxbeforewrap = addressmask + 1 - srcmask;

  // Check for impending buffer wraparound

  if (count > maxbeforewrap)
  {
    cmdbuf[0] = srcaddr >> 8;
    cmdbuf[1] = srcaddr & 0xFF;
    cmdbuf[2] = maxbeforewrap >> 8;
    cmdbuf[3] = maxbeforewrap & 0xFF;

    spi_master_transfer(spiport, cmdbuf, 4, buf, maxbeforewrap);

    srcaddr = socket_table[socket].RX_RAM_base;

    cmdbuf[0] = srcaddr >> 8;
    cmdbuf[1] = srcaddr & 0xFF;
    cmdbuf[2] = (count - maxbeforewrap) >> 8;
    cmdbuf[3] = (count - maxbeforewrap) & 0xFF;

    spi_master_transfer(spiport, cmdbuf, 4, buf + maxbeforewrap, count - maxbeforewrap);
  }
  else
  {
    cmdbuf[0] = srcaddr >> 8;
    cmdbuf[1] = srcaddr & 0xFF;
    cmdbuf[2] = count >> 8;
    cmdbuf[3] = count & 0xFF;

    spi_master_transfer(spiport, cmdbuf, 4, buf, count);
  }

  return status;
}

int W5200_write_transmit_ram(const uint32_t socket,
                             const uint16_t rampointer,
                             uint8_t *buf,
                             const size_t count)
{
  int status = 0;
  uint16_t dstmask;
  uint16_t dstaddr;
  uint16_t maxbeforewrap;
  uint8_t cmdbuf[4];

  // Validate parameters

  if (socket >= numsockets)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if (buf == NULL)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if (count == 0)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  dstmask = rampointer & addressmask;
  dstaddr = socket_table[socket].TX_RAM_base + dstmask;

  maxbeforewrap = addressmask + 1 - dstmask;

  // Check for impending buffer wraparound

  if (count > maxbeforewrap)
  {
    cmdbuf[0] = dstaddr >> 8;
    cmdbuf[1] = dstaddr & 0xFF;
    cmdbuf[2] = 0x80 | (maxbeforewrap >> 8);
    cmdbuf[3] = maxbeforewrap & 0xFF;

    spi_master_transfer(spiport, cmdbuf, 4, NULL, 0);
    spi_master_transfer(spiport, buf, maxbeforewrap, NULL, 0);

    dstaddr = socket_table[socket].TX_RAM_base;

    cmdbuf[0] = dstaddr >> 8;
    cmdbuf[1] = dstaddr & 0xFF;
    cmdbuf[2] = 0x80 | ((count - maxbeforewrap) >> 8);
    cmdbuf[3] = (count - maxbeforewrap) & 0xFF;

    spi_master_transfer(spiport, cmdbuf, 4, NULL, 0);
    spi_master_transfer(spiport, buf + maxbeforewrap, count - maxbeforewrap, NULL, 0);
  }
  else
  {
    cmdbuf[0] = dstaddr >> 8;
    cmdbuf[1] = dstaddr & 0xFF;
    cmdbuf[2] = 0x80 | (count >> 8);
    cmdbuf[3] = count & 0xFF;

    spi_master_transfer(spiport, cmdbuf, 4, NULL, 0);
    spi_master_transfer(spiport, buf, count, NULL, 0);
  }
  return status;
}

int wiznet_initialize(const uint32_t spiportnum,
                      const uint32_t sockets)
{
  int status = 0;
  int s;
  char socketname[16];

// Validate parameters

  if ((sockets < 1) || (sockets > W5200_MAX_SOCKETS))
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

// Save SPI port number

  spiport = spiportnum;

// Save the number of allowed sockets

  numsockets = sockets;

// Initialize mode register

  if ((status = W5200_write_register(W5200_MR, 0)))	// Disable ping block
    return status;

// Initialize interrupt mask register

  if ((status = W5200_write_register(W5200_IMR, 0))) 	// Disable interrupts
    return status;

// Initialize retry time

  if ((status = W5200_write_register(W5200_RTR+0, 2000 / 256)))	// 200 ms
    return status;

  if ((status = W5200_write_register(W5200_RTR+1, 2000 % 256)))	// 200 ms
    return status;

// Initialize retry count

  if ((status = W5200_write_register(W5200_RCR, 10)))
    return status;

// Initialize interrupt high time

  if ((status = W5200_write_register(W5200_INTLEVEL, 1)))	// 1 clock
    return status;

// Initialize socket interrupt mask register

  if ((status = W5200_write_register(W5200_IMR2, 0)))	// All disabled
    return status;

// Zero the socket table

  memset(socket_table, 0, sizeof(socket_table));

  for (s = 0; s < numsockets; s++)
  {

// Initialize memory size registers for this socket

    if ((status = W5200_write_register(W5200_Sn_RXMEM_SIZE(s),
         RAMSIZE_TABLE[numsockets].CONFIG)))
      return status;

    if ((status = W5200_write_register(W5200_Sn_TXMEM_SIZE(s),
         RAMSIZE_TABLE[numsockets].CONFIG)))
      return status;

// Precalculate transmit and receive buffer base addresses

    socket_table[s].TX_RAM_base = W5200_TX_RAM_ADDR + s*RAMSIZE_TABLE[numsockets].SIZE;
    socket_table[s].RX_RAM_base = W5200_RX_RAM_ADDR + s*RAMSIZE_TABLE[numsockets].SIZE;

// Initialize the transmit buffer pointers for this socket

    if ((status = W5200_write_register(W5200_Sn_TX_RD(s), 0x0000)))
      return status;

    if ((status = W5200_write_register(W5200_Sn_TX_WR(s), 0x0000)))
      return status;

// Initialize the receive buffer pointers for this socket

    if ((status = W5200_write_register(W5200_Sn_RX_RD(s), 0x0000)))
      return status;

    if ((status = W5200_write_register(W5200_Sn_RX_WR(s), 0x0000)))
      return status;

// Register a device driver for the socket

    memset(socketname, 0, sizeof(socketname));
    snprintf(socketname, sizeof(socketname), "socket%d:", s);

    if ((status = device_register_char(socketname, s, socket_open, socket_close,
                                       socket_write,  socket_read,
                                       socket_write_ready, socket_read_ready)))
      return status;
  }

// Precalculate address mask

  addressmask = RAMSIZE_TABLE[numsockets].SIZE - 1;

  return status;
}

int wiznet_set_hardware_address(const macaddress_t address)
{
  int i;
  int status = 0;

  for (i = 0; i < 6; i++)
    if ((status = W5200_write_register(W5200_SHAR+i, address[i])))
      return status;

  return status;
}

int wiznet_get_hardware_address(macaddress_t address)
{
  int i;
  int status = 0;

  for (i = 0; i < 6; i++)
    if ((status = W5200_read_register(W5200_SHAR+i, &address[i])))
      return status;

  return status;
}

int wiznet_configure_network(const ipv4address_t address,
                             const ipv4address_t subnet,
                             const ipv4address_t gateway)
{
  int i;
  int status = 0;

  for (i = 0; i < 4; i++)
    if ((status = W5200_write_register(W5200_SIPR+i, address[i])))
      return status;

  for (i = 0; i < 4; i++)
    if ((status = W5200_write_register(W5200_SUBR+i, subnet[i])))
      return status;

  for (i = 0; i < 4; i++)
    if ((status = W5200_write_register(W5200_GAR+i,  gateway[i])))
      return status;

  return status;
}

int wiznet_get_ipaddress(ipv4address_t address)
{
  int i;
  int status = 0;

  for (i = 0; i < 4; i++)
    if ((status = W5200_read_register(W5200_SIPR+i, &address[i])))
      return status;

  return status;
}

int wiznet_get_linkstate(uint32_t *linkstate)
{
  int status = 0;
  uint8_t data;

  if (linkstate == NULL)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if ((status = W5200_read_register(W5200_PSTATUS, &data)))
    return status;

  *linkstate = data & W5200_PSTATUS_LINK ? TRUE : FALSE;
  return status;
}

int wiznet_get_port(const uint32_t socket,
                    uint32_t *port)
{
  int status = 0;
  uint8_t hibyte, lobyte;

  if (socket >= numsockets)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if (port == NULL)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if ((status = W5200_read_register(W5200_Sn_SR(socket)+0, &hibyte)))
    return status;

  if ((status = W5200_read_register(W5200_Sn_SR(socket)+1, &lobyte)))
    return status;

  *port = (hibyte << 8) + lobyte;
  return status;
}

int wiznet_get_receive_ready(const uint32_t socket,
                             size_t *count)
{
  int status = 0;
  uint8_t hibyte, lobyte;

  if (socket >= numsockets)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if (count == NULL)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if ((status = W5200_read_register(W5200_Sn_RX_RSR(socket)+0, &hibyte)))
    return status;

  if ((status = W5200_read_register(W5200_Sn_RX_RSR(socket)+1, &lobyte)))
    return status;

  *count = (hibyte << 8) + lobyte;
  return status;
}

int wiznet_get_transmit_free(const uint32_t socket,
                             size_t *count)
{
  int status = 0;
  uint8_t hibyte, lobyte;

  if (socket >= numsockets)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if (count == NULL)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if ((status = W5200_read_register(W5200_Sn_TX_FSR(socket)+0, &hibyte)))
    return status;

  if ((status = W5200_read_register(W5200_Sn_TX_FSR(socket)+1, &lobyte)))
    return status;

  *count = (hibyte << 8) + lobyte;
  return status;
}

int wiznet_udp_open(const uint32_t socket,
                    const uint16_t port)
{
  int status = 0;
  uint16_t myport = port;
  uint8_t data;

  // Validate parameters

  if (socket >= numsockets)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  // Make sure requested socket is idle

  if ((status = W5200_read_register(W5200_Sn_SR(socket), &data)))
    return status;

  if (data != W5200_Sn_SR_SOCK_CLOSED)
  {
    errno_r = EALREADY;
    return __LINE__ - 3;
  }

  // Pick random ephemeral port

  while (myport == 0)
  {
    int i;
    uint32_t p;

    // Pick a random port number
    myport = 49152 + rand() % 16384;

    // See if it is already in use
    for (i = 0; i < W5200_MAX_SOCKETS; i++)
    {
      // Skip if this socket is not UDP
      if (status != W5200_Sn_SR_SOCK_UDP)
        continue;

      if ((status = wiznet_get_port(i, &p)))
        return status;

      // If we have a match, try another random port
      if (myport == p)
      {
        myport = 0;
        break;
      }
    }
  }

  if ((status = W5200_write_register(W5200_Sn_MR(socket), W5200_Sn_MR_UDP)))
    return status;

  if ((status = W5200_write_register(W5200_Sn_PORT(socket)+0, myport / 256)))
    return status;

  if ((status = W5200_write_register(W5200_Sn_PORT(socket)+1, myport % 256)))
    return status;

  if ((status = W5200_write_register(W5200_Sn_CR(socket), W5200_Sn_CR_OPEN)))
    return status;

  return status;
}

int wiznet_udp_receive_from(const uint32_t socket,
                            ipv4address_t srcaddr,
                            uint16_t *srcport,
                            uint8_t *buf,
                            size_t *count)
{
  int status = 0;
  size_t rxready;
  uint8_t hibyte, lobyte;
  uint16_t Sn_RX_RD;
  uint16_t word;

  // Validate parameters

  if (socket >= numsockets)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  // Get number of received bytes available

  if ((status = wiznet_get_receive_ready(socket, &rxready)))
    return status;

  // Error if no data available

  if (rxready == 0)
  {
    errno_r = ENODATA;
    return __LINE__ - 3;
  }

  // Get receive buffer read pointer

  if ((status = W5200_read_register(W5200_Sn_RX_RD(socket)+0, &hibyte)))
    return status;

  if ((status = W5200_read_register(W5200_Sn_RX_RD(socket)+1, &lobyte)))
    return status;

  Sn_RX_RD = (hibyte << 8) + lobyte;

  // Read source IP address from W5200 RAM

  if ((status = W5200_read_receive_ram(socket, Sn_RX_RD+0, (uint8_t *) srcaddr, 4)))
    return status;

  // Read source UDP port from W5200 RAM

  if ((status = W5200_read_receive_ram(socket, Sn_RX_RD+4, (uint8_t *) &word, 2)))
    return status;

  *srcport = ntohs(word);

  // Read UDP datagram size from W5200 RAM

  if ((status = W5200_read_receive_ram(socket, Sn_RX_RD+6, (uint8_t *) &word, 2)))
    return status;

  *count = ntohs(word);

  // Read UDP datagram from W5200 RAM

  if ((status = W5200_read_receive_ram(socket, Sn_RX_RD+8, buf, *count)))
    return status;

  // Advance Sn_RX_RD

  Sn_RX_RD += 8 + *count;

  if ((status = W5200_write_register(W5200_Sn_RX_RD(socket)+0, Sn_RX_RD >> 8)))
    return status;

  if ((status = W5200_write_register(W5200_Sn_RX_RD(socket)+1, Sn_RX_RD & 0xFF)))
    return status;

  // Issue RECV command

  if ((status = W5200_write_register(W5200_Sn_CR(socket), W5200_Sn_CR_RECV)))
    return status;

  return status;
}

int wiznet_udp_send_to(const uint32_t socket,
                       const ipv4address_t destaddr,
                       const uint32_t destport,
                       uint8_t *buf,
                       const uint32_t count)
{
  int status = 0;
  size_t txfree;
  uint8_t hibyte, lobyte;
  uint16_t Sn_TX_WR;

  // Validate parameters

  if (socket >= W5200_MAX_SOCKETS)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  // Make sure socket hardware is idle

  if ((status = W5200_read_register(W5200_Sn_CR(socket), &lobyte)))
    return status;

  if (lobyte != W5200_Sn_CR_IDLE)
  {
    errno_r = EBUSY;
    return __LINE__ - 3;
  }

  // Get number of transmit bytes free

  if ((status = wiznet_get_transmit_free(socket, &txfree)))
    return status;

  // Error if no room available

  if (count > txfree)
  {
    errno_r = ENOBUFS;
    return __LINE__ - 3;
  }

  // Set destination IP address

  if ((status = W5200_write_register(W5200_Sn_DIPR(socket)+0, destaddr[0])))
    return status;

  if ((status = W5200_write_register(W5200_Sn_DIPR(socket)+1, destaddr[1])))
    return status;

  if ((status = W5200_write_register(W5200_Sn_DIPR(socket)+2, destaddr[2])))
    return status;

  if ((status = W5200_write_register(W5200_Sn_DIPR(socket)+3, destaddr[3])))
    return status;

  // Set destination UDP port number

  if ((status = W5200_write_register(W5200_Sn_DPORT(socket)+0, destport >> 8)))
    return status;

  if ((status = W5200_write_register(W5200_Sn_DPORT(socket)+1, destport & 0xFF)))
    return status;

  // Get transmit buffer write pointer

  if ((status = W5200_read_register(W5200_Sn_TX_WR(socket)+0, &hibyte)))
    return status;

  if ((status = W5200_read_register(W5200_Sn_TX_WR(socket)+1, &lobyte)))
    return status;

  Sn_TX_WR = (hibyte << 8) + lobyte;

  // Write UDP datagram to W5200 RAM

  if ((status = W5200_write_transmit_ram(socket, Sn_TX_WR, buf, count)))
    return status;

  // Advance Sn_TX_WR

  Sn_TX_WR += count;

  if ((status = W5200_write_register(W5200_Sn_TX_WR(socket)+0, Sn_TX_WR >> 8)))
    return status;

  if ((status = W5200_write_register(W5200_Sn_TX_WR(socket)+1, Sn_TX_WR & 0xFF)))
    return status;

  // Issue SEND command

  if ((status = W5200_write_register(W5200_Sn_CR(socket), W5200_Sn_CR_SEND)))
    return status;

  return status;
}

int socket_open(char *name, unsigned int *subdevice)
{
  char namebuf[DEVICE_NAME_SIZE];
  char *devname;
  char *protocol;
  char *localport;
  char *remotehost;
  char *remoteport;
  int fd;

  // Copy device name to temporary buffer

  memset(namebuf, 0, sizeof(namebuf));
  strlcpy(namebuf, name, sizeof(namebuf));

  // Split device name into its components

  devname = strtok(name, ":");
  protocol = strtok(NULL, ",");
  localport = strtok(NULL, ",");
  remotehost = strtok(NULL, ",");
  remoteport = strtok(NULL, ",");

  fd = device_lookup(devname);
  if (fd < 0) return fd;

  return 0;
}

int socket_close(unsigned int subdevice)
{
  return 0;
}

int socket_write(unsigned int subdevice, char *buf, unsigned int count)
{
  return 0;
}

int socket_read(unsigned int subdevice, char *buf, unsigned int count)
{
  return 0;
}

int socket_write_ready(unsigned int subdevice)
{
  int status;
  size_t count;

  status = wiznet_get_transmit_free(subdevice, &count);
  if (status) return status;

  if (count)
    return TRUE;
  else
    return FALSE;
}

int socket_read_ready(unsigned int subdevice)
{
  int status;
  size_t count;

  status = wiznet_get_receive_ready(subdevice, &count);
  if (status) return status;

  if (count)
    return TRUE;
  else
    return FALSE;
}
