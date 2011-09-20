/* W5200 Device Driver */

// $Id$

static const char revision[] = "$Id$";

#include <spi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <W5200.h>

static uint32_t spiport;

int W5200_initialize(uint32_t spiportnum)
{
  spiport = spiportnum;
  return spimaster_init(spiport, 0, 281250, 1);
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
