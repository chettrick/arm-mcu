/******************************************************************************/
/*                                                                            */
/*        Simple serial console I/O routines for the LPC2366 ARM MCU          */
/*                                                                            */
/******************************************************************************/

// $Id$

#include <cpu.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

/* Define relocatable UART register definitions */

static unsigned long int UARTBASE = UART0_BASE_ADDR;

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

void conio_init(unsigned port, unsigned long int baudrate)
{
  unsigned short int b;

  switch (port)
  {
    case 0 :
      UARTBASE = UART0_BASE_ADDR;
      PINSEL0 &= 0xFFFFFF0F;		// Enable UART 0 I/O pins
      PINSEL0 |= 0x00000050;
      break;

    case 1 :
      UARTBASE = UART1_BASE_ADDR;
      PINSEL0 &= 0x3FFFFFFF;		// Enable UART 1 I/O pins
      PINSEL0 |= 0x40000000;
      PINSEL1 &= 0xFFFFFFFC;
      PINSEL1 |= 0x00000001;
      break;

    case 2 :
      UARTBASE = UART2_BASE_ADDR;
      PINSEL0 &= 0xFF0FFFFF;		// Enable UART 2 I/O pins
      PINSEL0 |= 0x00500000;
      break;

    case 3 :
      UARTBASE = UART3_BASE_ADDR;
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

/* Return 1 if key pressed */

unsigned char keypressed(void)
{
  return (UxLSR & 0x01);
}

/* Send a string */

void cputs(char *s)
{
  while (*s)
    putch(*s++);
}

/* Receive a string, with rudimentary line editing */

void cgets(char *s, int bufsize)
{
  char *p;
  int c;

  memset(s, 0, bufsize);

  p = s;

  for (p = s; p < s + bufsize-1;)
  {
    c = getch();
    switch (c)
    {
      case '\r' :
      case '\n' :
        putch('\r');
        putch('\n');
        *p = '\n';
        return;

      case '\b' :
        if (p > s)
        {
          *p-- = 0;
          putch('\b');
          putch(' ');
          putch('\b');
        }
        break;

      default :
        putch(c);
        *p++ = c;
        break;
    }
  }

  return;
}
