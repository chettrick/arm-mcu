/* Simple serial console I/O test program */

// $Id: test_conio.c,v 1.1 2007-02-07 22:46:09 cvs Exp $

#include <lpc2119/conio.h>
#include <lpc2119/io.h>

#include <stdio.h>
#include <string.h>

int main(void)
{
  char buf[32];

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

  conio_init(19200);

  puts("\033[H\033[2JLPC2119 Console I/O Test\n");

  for (;;)
  {
    printf("Enter a string: ");
    fgets(buf, sizeof(buf), stdin);
    if (strlen(buf)) if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;
    printf("You entered %ld bytes, '%s'\n", strlen(buf), buf);
  }
}
