/******************************************************************************/
/*                                                                            */
/*     Simple serial console I/O routines for the Phillips LPC2119 ARM MCU    */
/*                                                                            */
/******************************************************************************/

// $Id: conio.c,v 1.1 2006-12-12 21:57:48 cvs Exp $

#include <stdio.h>
#include <string.h>

#include "conio.h"

/* Initialize serial console */

void conio_init(unsigned long int baudrate)
{
}

/* Send 1 character */

void putch(unsigned char c)
{
}

/* Receive 1 character */

int getch(void)
{

  return 0;
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
