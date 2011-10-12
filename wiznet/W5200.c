/* W5200 Device Driver */

// $Id$

static const char revision[] = "$Id$";

#include <errno.h>
#include <spi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiznet.h>
#include <W5200.h>

#define errno_r (*(__errno()))

static uint32_t spiport = 0;
static int numsockets = 0;
static uint32_t addressmask = 0;

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
  { W5200_RAMSIZE,	W5200_RAMSIZE_CONFIG_WHOLE	},
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

int W5200_write_register(const uint16_t address, const uint8_t data)
{
  uint8_t txbuf[5];

  txbuf[0] = (address >> 8) & 0xFF;
  txbuf[1] = address & 0xFF;
  txbuf[2] = 0x80;
  txbuf[3] = 0x01;
  txbuf[4] = data;

  return spimaster_transfer(spiport, txbuf, 5, NULL, 0);
}

int W5200_read_register(const uint16_t address, uint8_t *data)
{
  uint8_t txbuf[4];

  txbuf[0] = (address >> 8) & 0xFF;
  txbuf[1] = address & 0xFF;
  txbuf[2] = 0x00;
  txbuf[3] = 0x01;

  return spimaster_transfer(spiport, txbuf, 4, data, 1);
}

static volatile uint32_t delaycounter = 0;

void wiznet_tick(void)
{
  if (delaycounter)
    delaycounter--;
}

int wiznet_initialize(const uint32_t spiportnum,
                      const int sockets)
{
  int status = 0;
  int s;

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

int wiznet_get_linkstate(int *linkstate)
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

int wiznet_get_port(const int socket,
                    uint16_t *port)
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

int wiznet_get_receive_ready(const int socket,
                             uint32_t *count)
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

int wiznet_get_transmit_free(const int socket,
                             uint32_t *count)
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

int wiznet_read_receive_ram(const int socket,
                            uint32_t *rampointer,
                            void *dst,
                            const unsigned int count)
{
  int status = 0;
  uint8_t txbuf[4];

  // Validate parameters

  if (socket >= numsockets)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if (dst == NULL)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  txbuf[0] = (*rampointer >> 8) & 0xFF;
  txbuf[1] = *rampointer & 0xFF;
  txbuf[2] = 0x00;
  txbuf[3] = 0x01;

  status = spimaster_transfer(spiport, txbuf, 4, dst, count);

  *rampointer += count;

  return status;
}

int wiznet_udp_open(const int socket,
                    uint16_t port)
{
  int status = 0;
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

  while (port == 0)
  {
    int i;
    uint16_t p;

    // Pick a random port number
    port = 49152 + rand() % 16384;

    // See if it is already in use
    for (i = 0; i < W5200_MAX_SOCKETS; i++)
    {
      // Skip if this socket is not UDP
      if (status != W5200_Sn_SR_SOCK_UDP)
        continue;

      if ((status = wiznet_get_port(i, &p)))
        return status;

      // If we have a match, try another random port
      if (port == p)
      {
        port = 0;
        break;
      }
    }
  }

  if ((status = W5200_write_register(W5200_Sn_MR(socket), W5200_Sn_MR_UDP)))
    return status;

  if ((status = W5200_write_register(W5200_Sn_PORT(socket)+0, port / 256)))
    return status;

  if ((status = W5200_write_register(W5200_Sn_PORT(socket)+1, port % 256)))
    return status;

  if ((status = W5200_write_register(W5200_Sn_CR(socket), W5200_Sn_CR_OPEN)))
    return status;

  return status;
}

int wiznet_udp_receive(const int socket,
                       ipv4address_t srcaddr,
                       uint16_t *srcport,
                       void *buf,
                       uint32_t *count)
{
  int status = 0;
  uint32_t rxready;
  uint8_t hibyte, lobyte;
  uint32_t rampointer;

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

  rampointer = socket_table[socket].RX_RAM_base + (((hibyte << 8) + lobyte) & addressmask);

  // Read source IP address from W5200 RAM

  if ((status = wiznet_read_receive_ram(socket, &rampointer, srcaddr, 4)))
    return status;

  // Read source UDP port from W5200 RAM

  if ((status = wiznet_read_receive_ram(socket, &rampointer, srcport, 2)))
    return status;

  // Read UDP datagram size from W5200 RAM

  if ((status = wiznet_read_receive_ram(socket, &rampointer, count, 2)))
    return status;

  // Read UDP datagram from W5200 RAM

  if ((status = wiznet_read_receive_ram(socket, &rampointer, buf, *count)))
    return status;

  return status;
}

int wiznet_udp_send(const int socket,
                    const ipv4address_t destaddr,
                    const uint16_t destport,
                    void *buf,
                    const uint32_t count)
{
  int status = 0;
  uint32_t free;

  // Validate parameters

  if (socket >= W5200_MAX_SOCKETS)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  // Get number of transmit bytes free

  if ((status = wiznet_get_transmit_free(socket, &free)))
    return status;

  // Error if no room available

  if (count > free)
  {
    errno_r = ENOBUFS;
    return __LINE__ - 3;
  }

  return status;
}
