/* W5100 Device Driver */

// $Id$

static const char revision[] = "$Id$";

#include <errno.h>
#include <spi.h>
#include <stdlib.h>
#include <wiznet.h>
#include <W5100.h>

#define errno_r (*(__errno()))

static uint32_t spiport;

int W5100_write_register(const uint16_t address, const uint8_t data)
{
  uint8_t txbuf[4];

  txbuf[0] = 0xF0;
  txbuf[1] = (address >> 8) & 0xFF;
  txbuf[2] = address & 0xFF;
  txbuf[3] = data;

  return spimaster_transfer(spiport, txbuf, 4, NULL, 0);
}

int W5100_read_register(const uint16_t address, uint8_t *data)
{
  uint8_t txbuf[3];

  txbuf[0] = 0x0F;
  txbuf[1] = (address >> 8) & 0xFF;
  txbuf[2] = address & 0xFF;

  return spimaster_transfer(spiport, txbuf, 3, data, 1);
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

// Save SPI port number

  spiport = spiportnum;

// Initialize mode register

  if ((status = W5100_write_register(W5100_MR, 0)))
    return status;

  return status;
}

int wiznet_set_hardware_address(const macaddress_t address)
{
  int i;
  int status = 0;

  for (i = 0; i < 6; i++)
    if ((status = W5100_write_register(W5100_SHAR+i, address[i])))
      return status;

  return status;
}

int wiznet_get_hardware_address(macaddress_t address)
{
  int i;
  int status = 0;

  for (i = 0; i < 6; i++)
    if ((status = W5100_read_register(W5100_SHAR+i, &address[i])))
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
    if ((status = W5100_write_register(W5100_SIPR+i, address[i])))
      return status;

  for (i = 0; i < 4; i++)
    if ((status = W5100_write_register(W5100_SUBR+i, subnet[i])))
      return status;

  for (i = 0; i < 4; i++)
    if ((status = W5100_write_register(W5100_GAR+i,  gateway[i])))
      return status;

  return status;
}

int wiznet_get_ipaddress(ipv4address_t address)
{
  int i;
  int status = 0;

  for (i = 0; i < 4; i++)
    if ((status = W5100_read_register(W5100_SIPR+i, &address[i])))
      return status;

  return status;
}

int wiznet_get_linkstate(int *linkstate)
{
  int status = 0;

  *linkstate = TRUE;
  return status;
}
