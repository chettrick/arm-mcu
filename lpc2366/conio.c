/******************************************************************************/
/*                                                                            */
/*     Simple serial console I/O routines for the Phillips LPC2366 ARM MCU    */
/*                                                                            */
/******************************************************************************/

// $Id: conio.c,v 1.3 2007-08-17 20:17:36 cvs Exp $

#include <stdio.h>
#include <string.h>

#include "conio.h"
#include "io.h"

unsigned int CPUFREQ = 72000000;

/* Define relocatable UART register definitions */

unsigned int UARTBASE = UART0_BASE_ADDR;

#define UxRBR          (*(volatile unsigned long *)(UARTBASE + 0x00))
#define UxTHR          (*(volatile unsigned long *)(UARTBASE + 0x00))
#define UxDLL          (*(volatile unsigned long *)(UARTBASE + 0x00))
#define UxDLM          (*(volatile unsigned long *)(UARTBASE + 0x04))
#define UxIER          (*(volatile unsigned long *)(UARTBASE + 0x04))
#define UxIIR          (*(volatile unsigned long *)(UARTBASE + 0x08))
#define UxFCR          (*(volatile unsigned long *)(UARTBASE + 0x08))
#define UxLCR          (*(volatile unsigned long *)(UARTBASE + 0x0C))
#define UxMCR          (*(volatile unsigned long *)(UARTBASE + 0x10))
#define UxLSR          (*(volatile unsigned long *)(UARTBASE + 0x14))
#define UxMSR          (*(volatile unsigned long *)(UARTBASE + 0x18))
#define UxSCR          (*(volatile unsigned long *)(UARTBASE + 0x1C))
#define UxACR          (*(volatile unsigned long *)(UARTBASE + 0x20))
#define UxICR          (*(volatile unsigned long *)(UARTBASE + 0x24))
#define UxFDR          (*(volatile unsigned long *)(UARTBASE + 0x28))
#define UxTER          (*(volatile unsigned long *)(UARTBASE + 0x30))

/* Initialize serial console */

void conio_init(unsigned long int baudrate)
{
  unsigned short int b;

  switch (UARTBASE)
  {
    case UART0_BASE_ADDR :
      PINSEL0 &= 0xFFFFFF0F;		// Enable UART 0 I/O pins
      PINSEL0 |= 0x00000050;
      break;

    case UART1_BASE_ADDR :
      PINSEL0 &= 0x3FFFFFFF;		// Enable UART 1 I/O pins
      PINSEL0 |= 0x40000000;
      PINSEL1 &= 0xFFFFFFFC;
      PINSEL1 |= 0x00000001;
      break;

    case UART2_BASE_ADDR :
      PINSEL0 &= 0xFF0FFFFF;		// Enable UART 2 I/O pins
      PINSEL0 |= 0x00500000;
      break;

    case UART3_BASE_ADDR :
      PINSEL0 &= 0xFFFFFFF0;		// Enable UART 3 I/O pins
      PINSEL0 |= 0x0000000A;
      break;

    default :				// Unrecognized UART base address
      return;				// Do nothing
  }

  UxFDR = 0x49;				// Scale peripheral clock by 4/13

  b = CPUFREQ/208/baudrate;

  UxIER = 0x00;				// Disable UART interrupts
  UxLCR = 0x80;
  UxDLM = b / 256;
  UxDLL = b % 256;
  UxLCR = 0x03;				// Always 8 bits no parity 1 stop
  UxFCR = 0x01;				// Enable FIFO's
}

/* Send 1 character */

void putch(unsigned char c)
{
  if (c == '\n') putch('\r');

  while ((UxLSR & 0x20) == 0);
  UxTHR = c;
}

/* Receive 1 character */

unsigned char getch(void)
{
  while ((UxLSR & 0x01) == 0);
  return UxRBR;
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
