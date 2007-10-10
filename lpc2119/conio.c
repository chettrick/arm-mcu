/******************************************************************************/
/*                                                                            */
/*     Simple serial console I/O routines for the Phillips LPC2119 ARM MCU    */
/*                                                                            */
/******************************************************************************/

// $Id: conio.c,v 1.6 2007-10-10 03:24:05 cvs Exp $

#include <conio.h>
#include <cpu.h>
#include <stdio.h>
#include <string.h>

/* Initialize serial console */

void conio_init(unsigned long int uartaddr, unsigned long int baudrate)
{
  unsigned short int b;

  PINSEL0 &= 0xFFFFFFF0;		// Enable UART 0 I/O pins
  PINSEL0 |= 0x00000005;

  b = CPUFREQ/16/baudrate;

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
