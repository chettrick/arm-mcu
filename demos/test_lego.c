/* LEGO Power Functions Remote Control test program */

// Reference "LEGO Power Functions RC Version 1.20"

// $Id: test_gpio.c 3199 2011-10-18 11:28:12Z svn $

static const char revision[] = "$Id: test_gpio.c 3199 2011-10-18 11:28:12Z svn $";

#include <cpu.h>
#include <stdint.h>

#ifdef FEZ_CERB40
#define LEDPIN		GPIOPIN38
#define LEDOUT		GPIOPIN38OUT
#define DELAY38KHZ	182
#endif

typedef enum
{
  BIT_LOW	= 0,
  BIT_HIGH	= 1,
  BIT_START	= 2,
  BIT_STOP	= 3,
} lego_bit_t;

const int LEGO_BIT_LOW_TIMES[] = { 10, 21, 39, 39 };  // Cycles of silence following the mark

static void SendBit(lego_bit_t bit)
{
  unsigned long int n, i, j;

// Send mark, 6 cycles of 38 kHz square wave

  n = 12;

  for (i = 1; i <= 12; i++)
  {
    for (j = 0; j < DELAY38KHZ; j++);

    LEDOUT = i;
  }

// Send space, n cycles of silence

  n = 2*LEGO_BIT_LOW_TIMES[bit];

  for (i = 1; i <= n; i++)
  {
    for (j = 0; j < DELAY38KHZ; j++);

    LEDOUT = 0;
  }
}

static void SendFrame(uint16_t data)
{
  int i;
  uint8_t LRC;

  LRC = (0xF ^ ((data >> 8) & 0x0F) ^ ((data >> 4) & 0x0F) ^ (data & 0x0F)) & 0x0F;

  data <<= 4;
  data &= 0xFFF0;
  data |= LRC;

  SendBit(BIT_START);

  for (i = 0; i < 16; i++)
  {
    SendBit(data >> 15);

    data <<= 1;
  }

  SendBit(BIT_STOP);
}

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);

  gpiopin_configure(LEDPIN, GPIOPIN_OUTPUT);

  LEDOUT = 0;

  SendFrame(0);
}
