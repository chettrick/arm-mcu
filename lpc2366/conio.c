/******************************************************************************/
/*                                                                            */
/*     Simple serial console I/O routines for the Phillips LPC2366 ARM MCU    */
/*                                                                            */
/******************************************************************************/

// $Id: conio.c,v 1.1 2007-03-26 18:33:25 cvs Exp $

#include <stdio.h>
#include <string.h>

#include "conio.h"
#include "io.h"

unsigned int CPUFREQ = 72000000;

/* Initialize serial console */

void conio_init(unsigned long int baudrate)
{
  unsigned short int b;

  PINSEL0 &= 0xFFFFFF0F;		// Enable UART 0 I/O pins
  PINSEL0 |= 0x00000050;

  U0FDR = 0x49;				// Scale peripheral clock by 4/13

  b = CPUFREQ/208/baudrate;

  U0IER = 0x00;				// Disable UART interrupts
  U0LCR = 0x80;
  U0DLM = b / 256;
  U0DLL = b % 256;
  U0LCR = 0x03;				// Always 8 bits no parity 1 stop
  U0FCR = 0x01;				// Enable FIFO's
}

/* Send 1 character */

void putch(unsigned char c)
{
  if (c == '\n') putch('\r');

  while ((U0LSR & 0x20) == 0);
  U0THR = c;
}

/* Receive 1 character */

unsigned char getch(void)
{
  while ((U0LSR & 0x01) == 0);
  return U0RBR;
}

/* Send a string */

void cputs(char *s)
{
  while (*s)
    putch(*s++);
}

/* Override fgets() with a version that does line editing */

char *fgets(char *s, int bufsize, FILE *f)
{
  char *p;
  int c;

  memset(s, 0, bufsize);

  p = s;

  for (p = s; p < s + bufsize-1;)
  {
    c = getchar();
    switch (c)
    {
      case '\r' :
      case '\n' :
        putchar('\r');
        putchar('\n');
        *p = '\n';
        return s;

      case '\b' :
        if (p > s)
        {
          *p-- = 0;
          putchar('\b');
          putchar(' ');
          putchar('\b');
        }
        break;

      default :
        putchar(c);
        *p++ = c;
        break;
    }
  }

  return s;
}
