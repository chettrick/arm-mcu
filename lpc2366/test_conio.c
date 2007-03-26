/* Simple serial console I/O test program */

// $Id: test_conio.c,v 1.1 2007-03-26 18:33:25 cvs Exp $

#include <lpc2366/conio.h>
#include <lpc2366/io.h>

#include <stdio.h>
#include <string.h>

int main(void)
{
  char buf[32];

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

  conio_init(19200);

  puts("\033[H\033[2JLPC2366 Console I/O Test\n");

  for (;;)
  {
    printf("Enter a string: ");
    fgets(buf, sizeof(buf), stdin);
    if (strlen(buf)) if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;
    printf("You entered %ld bytes, '%s'\n", strlen(buf), buf);
  }
}
