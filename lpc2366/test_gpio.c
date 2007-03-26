/* Simple bit twiddler test program */

// $Id: test_gpio.c,v 1.1 2007-03-26 18:33:25 cvs Exp $

#include <lpc2366/io.h>

int main(void)
{
  unsigned long int i;

  MAMCR = 2;			// MAM functions fully enabled
  MAMTIM = 3;			// 3 CPU clocks per fetch cycle

/* Configure clock generators */

  SCS = 0x00000021;		// Turn on main oscillator, fast GPIO
  while (!(SCS & (1 << 6)));	// Wait for main oscillator startup

  CLKSRCSEL = 1;		// PLL source is main oscillator

  PLLCFG = 11;			// N=1, M=12 (Fin=12 MHz, Fref=12 MHz, Fcco=288 MHz)
  PLLCON = 1;			// Enable PLL
  PLLFEED = 0xAA;
  PLLFEED = 0x55;

  while (!(PLLSTAT & (1 << 26))); // Wait for PLL lock

  CCLKCFG = 3;			// CPU clock is Fcco/4 (72 MHz)
  USBCLKCFG = 5;		// USB clock is Fcco/6 (48 MHz)

  PLLCON = 3;			// Connect PLL
  PLLFEED = 0xAA;
  PLLFEED = 0x55;

/* Configure P0 pins */

  PCLKSEL1 = 0x00000004;	// GPIO peripheral clock is CCLK/1

  PINSEL0 = 0x00000000;		// Every P0 pin is a GPIO
  PINSEL1 = 0x00000000;

  FIO0MASK = 0x00000000;	// Every P0 pin is unmasked
  FIO0DIR = 0xFFFFFFFF;		// Every P0 pin is an output

  for (i = 0;; i++)
    FIO0PIN = i;
}
