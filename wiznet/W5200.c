/* W5200 Device Driver */

// $Id$

static const char revision[] = "$Id$";

#include <spi.h>
#include <stdlib.h>
#include <W5200.h>

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

static uint32_t spiport;
static volatile uint32_t delaycounter = 0;

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

int W5200_initialize(const uint32_t spiportnum)
{
  int status = 0;

// Save SPI port number

  spiport = spiportnum;

// Initialize mode register

  if ((status = W5200_write_register(W5200_MR, 0)))
    return status;

  return status;
}

int W5200_set_hardware_address(const macaddress_t address)
{
  int i;
  int status = 0;

  for (i = 0; i < 6; i++)
    if ((status = W5200_write_register(W5200_SHAR+i, address[i])))
      return status;

  return status;
}

int W5200_get_hardware_address(macaddress_t address)
{
  int i;
  int status = 0;

  for (i = 0; i < 6; i++)
    if ((status = W5200_read_register(W5200_SHAR+i, &address[i])))
      return status;

  return status;
}

int W5200_configure_network(const ipv4address_t address,
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

int W5200_get_ipaddress(ipv4address_t address)
{
  int i;
  int status = 0;

  for (i = 0; i < 4; i++)
    if ((status = W5200_read_register(W5200_SIPR+i, &address[i])))
      return status;

  return status;
}

int W5200_get_linkstate(int *linkstate)
{
  int status = 0;
  uint8_t data;

  if ((status = W5200_read_register(W5200_PSTATUS, &data)))
    return status;

  *linkstate = data & W5200_PSTATUS_LINK ? TRUE : FALSE;
  return status;
}

void W5200_tick(void)
{
  if (delaycounter)
    delaycounter--;
}
