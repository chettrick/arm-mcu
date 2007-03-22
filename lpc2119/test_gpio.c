/* Simple bit twiddler test program */

// $Id: test_gpio.c,v 1.2 2007-03-22 16:38:20 cvs Exp $

#include <lpc2119/io.h>

int main(void)
{
  unsigned long int i;

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

  for (i = 0;; i++)
  {
    IO0PIN = i;
    IO1PIN = i;
  }
}
