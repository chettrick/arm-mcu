/* W5200 Device Driver */

// $Id$

static const char revision[] = "$Id$";

#include <errno.h>
#include <spi.h>
#include <stdlib.h>
#include <wiznet.h>
#include <W5200.h>

#define errno_r (*(__errno()))

static uint32_t spiport;

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

int wiznet_initialize(const uint32_t spiportnum)
{
  int status = 0;
  int s;

// Save SPI port number

  spiport = spiportnum;

// Initialize mode register

  if ((status = W5200_write_register(W5200_MR, 0)))		// Disable ping block
    return status;

// Initialize interrupt mask register

  if ((status = W5200_write_register(W5200_IMR, 0)))		// Disable common interrupts
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

  if ((status = W5200_write_register(W5200_IMR2, 0)))		// All disabled
    return status;

// Initialize memory size registers

  for (s = 0; s < W5200_MAX_SOCKETS; s++)
  {
    if ((status = W5200_write_register(W5200_Sn_RXMEMSIZE(s), 2))) // 2K RAM
      return status;

    if ((status = W5200_write_register(W5200_Sn_TXMEM_SIZE(s), 2))) // 2K RAM
      return status;
  }

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

  if ((status = W5200_read_register(W5200_PSTATUS, &data)))
    return status;

  *linkstate = data & W5200_PSTATUS_LINK ? TRUE : FALSE;
  return status;
}

int wiznet_udp_open(int socket, uint16_t sourceport)
{
  int status = 0;
  uint8_t data;

  if ((status = W5200_write_register(W5200_Sn_MR(socket), W5200_Sn_MR_UDP)))
    return status;

  if ((status = W5200_write_register(W5200_Sn_PORT(socket), sourceport / 256)))
    return status;

  if ((status = W5200_write_register(W5200_Sn_PORT(socket), sourceport % 256)))
    return status;

  if ((status = W5200_write_register(W5200_Sn_CR(socket), W5200_Sn_CR_OPEN)))
    return status;

  delaycounter = 10;

  while (delaycounter > 0)
  {
    if ((status = W5200_read_register(W5200_Sn_SR(socket), &data)))
      return status;

    if (data == W5200_Sn_SR_SOCK_UDP)
    {
      delaycounter = 0;
      return 0;
    }  
  }

  errno_r = ETIMEDOUT;
  return __LINE__;
}
