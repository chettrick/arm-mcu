/* W5200 Device Driver */

// $Id$

static const char revision[] = "$Id$";

#include <spi.h>
#include <stdint.h>
#include <stdlib.h>
#include <W5200.h>

static uint32_t spiport;

int W5200_initialize(uint32_t spiportnum)
{
  int status;

// Save SPI port number

  spiport = spiportnum;

// Initialize mode register

  if ((status = W5200_write_register(W5200_MR, W5200_MR_PB)))
    return status;

  return 0;
}

int W5200_write_register(uint16_t address, uint8_t data)
{
  uint8_t txbuf[5];

  txbuf[0] = (address >> 8) & 0xFF;
  txbuf[1] = address & 0xFF;
  txbuf[2] = 0x80;
  txbuf[3] = 0x01;
  txbuf[4] = data;

  return spimaster_transfer(spiport, txbuf, 5, NULL, 0);
}

int W5200_read_register(uint16_t address, uint8_t *data)
{
  uint8_t txbuf[4];

  txbuf[0] = (address >> 8) & 0xFF;
  txbuf[1] = address & 0xFF;
  txbuf[2] = 0x00;
  txbuf[3] = 0x01;

  return spimaster_transfer(spiport, txbuf, 4, data, 1);
}

int W5200_set_hardware_address(uint8_t *address)
{
  int i;
  int status;

  for (i = 0; i < 6; i++)
    if ((status = W5200_write_register(W5200_SHAR+i, *address++)))
      return status;

  return 0;
}

int W5200_get_hardware_address(uint8_t *address)
{
  int i;
  int status;

  for (i = 0; i < 6; i++)
    if ((status = W5200_read_register(W5200_SHAR+i, address++)))
      return status;

  return 0;
}

int W5200_configure_network(uint32_t ipaddress, uint32_t subnet, uint32_t gateway)
{
  int i;
  int status;

  for (i = 0; i < 4; i++)
    if ((status = W5200_write_register(W5200_SIPR+i, (ipaddress >> ((3-i)*8)) & 0xFF)))
      return status;

  for (i = 0; i < 4; i++)
    if ((status = W5200_write_register(W5200_SUBR+i, (ipaddress >> ((3-i)*8)) & 0xFF)))
      return status;

  for (i = 0; i < 4; i++)
    if ((status = W5200_write_register(W5200_GAR+i,  (ipaddress >> ((3-i)*8)) & 0xFF)))
      return status;

  return 0;
}
