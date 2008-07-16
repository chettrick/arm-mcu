/******************************************************************************/
/*                                                                            */
/*   Simple serial console I/O routines for the Atmel AT91SAM7S256 ARM MCU    */
/*                                                                            */
/******************************************************************************/

// $Id: conio.c,v 1.4 2008-07-16 15:40:05 cvs Exp $

#include <cpu.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

/* Define relocatable UART register definitions */

static unsigned long int UARTBASE = (unsigned long int) AT91C_BASE_US0;

#define US_CR	(*(volatile unsigned long *)(UARTBASE + 0x00))
#define US_MR	(*(volatile unsigned long *)(UARTBASE + 0x04))
#define US_CSR	(*(volatile unsigned long *)(UARTBASE + 0x14))
#define US_RHR	(*(volatile unsigned long *)(UARTBASE + 0x18))
#define US_THR	(*(volatile unsigned long *)(UARTBASE + 0x1C))
#define US_BRGR	(*(volatile unsigned long *)(UARTBASE + 0x20))

/* Initialize serial console */

void conio_init(unsigned port, unsigned long int baudrate)
{

// Configure peripheral clock and I/O pins for UART

  switch (port)
  {
    case 0 :
      UARTBASE = (unsigned long int) AT91C_BASE_US0;
      *AT91C_PMC_PCER = 0x00000040;
      *AT91C_PIOA_ASR = 0x00000060;
      *AT91C_PIOA_PDR = 0x00000060;
      break;

    case 1 :
      UARTBASE = (unsigned long int) AT91C_BASE_US1;
      *AT91C_PMC_PCER = 0x00000080;
      *AT91C_PIOA_ASR = 0x00600000;
      *AT91C_PIOA_PDR = 0x00600000;
      break;
  }

// Configure UART

  US_CR = 0x00000050;
  US_MR = 0x000008C0;
  US_BRGR = CPUFREQ/16/baudrate;
}

/* Send 1 character */

void putch(unsigned char c)
{
  if (c == '\n') putch('\r');

  while ((US_CSR & AT91C_US_TXRDY) == 0);
  US_THR = c;
}

/* Receive 1 character */

unsigned char getch(void)
{
  while ((US_CSR & AT91C_US_RXRDY) == 0);
  return US_RHR;
}

/* Return 1 if key pressed */

unsigned char keypressed(void)
{
  return (US_CSR & AT91C_US_RXRDY);
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
