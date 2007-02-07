/* Simple bit twiddler test program */

// $Id: test_gpio.c,v 1.1 2007-02-07 22:46:10 cvs Exp $

#include <lpc2119/io.h>

int main(void)
{
  unsigned char a;
  unsigned int i;
  unsigned volatile char dummy;

  MAMCR = 2;			// MAM functions fully enabled

  VPBDIV = 0x01;		// pclk = cclk

  PLLCFG = (0x01 << 5) + 0x02;	// M=3, P=2
  PLLCON = 1;
  PLLFEED = 0xAA;
  PLLFEED = 0x55;
  while((PLLSTAT & 0x400) == 0);
  PLLCON = 3;
  PLLFEED = 0xAA;
  PLLFEED = 0x55;

  PINSEL0 = 0x00000000;	// Every pin is a GPIO
  PINSEL1 = 0x00000000;
  PINSEL2 = 0x00000030;

  IO0DIR = 0xFFFFFFFF;	// Every pin is an output
  IO1DIR = 0xFFFFFFFF;

  for (a = 0;; a++)
  {
    for (i = 0; i < 10000; i++) dummy++;

    IO0PIN = (a << 24) + (a << 16) + (a << 8) + a;
    IO1PIN = (a << 24) + (a << 16) + (a << 8) + a;
  }
}
