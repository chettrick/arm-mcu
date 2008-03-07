/******************************************************************************/
/*                                                                            */
/*      Simple serial console I/O routines for the STR912FAW44 ARM MCU        */
/*                                                                            */
/******************************************************************************/

// $Id: conio.c,v 1.1 2008-03-07 13:51:19 cvs Exp $

#include <conio.h>
#include <cpu.h>
#include <stdio.h>
#include <string.h>

#define UART0_BASE_ADDR 0x40013800

static unsigned long int UARTBASE = UART0_BASE_ADDR;

/* Define relocatable UART registers */

#define UxDR	(*((volatile unsigned short int *) (UARTBASE + 0x00)))
#define	UxFR	(*((volatile unsigned short int *) (UARTBASE + 0x18)))
#define UxIBRD	(*((volatile unsigned short int *) (UARTBASE + 0x24)))
#define UxFBRD	(*((volatile unsigned short int *) (UARTBASE + 0x28)))
#define UxLCR	(*((volatile unsigned short int *) (UARTBASE + 0x2C)))
#define UxCR	(*((volatile unsigned short int *) (UARTBASE + 0x30)))

/* Initialize serial console */

void conio_init(unsigned port, unsigned long int baudrate)
{
}

/* Send 1 character */

void putch(unsigned char c)
{
  if (c == '\n') putch('\r');

  while (UxFR & 0x20);
  UxDR = c;
}

/* Receive 1 character */

unsigned char getch(void)
{
  while (UxFR & 0x10);
  return UxDR;
}

/* Return 1 if key pressed */

unsigned char keypressed(void)
{
  return !(UxFR & 0x10);
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
