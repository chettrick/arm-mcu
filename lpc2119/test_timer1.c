/* Simple timer interrupt test program */

// $Id: test_timer1.c,v 1.1 2007-02-07 22:46:10 cvs Exp $

#include <lpc2119/conio.h>
#include <lpc2119/interrupt.h>
#include <lpc2119/io.h>

#include <stdio.h>
#include <string.h>

#define TRUE	1
#define	FALSE	0

volatile int Timer1Flag = FALSE;

__attribute__ ((__interrupt__)) void Timer1ISR(void)
{
  Timer1Flag = TRUE;
  T1IR = 0x01;
  VICVectAddrRead = 0;
}

int main(void)
{
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

  puts("\033[H\033[2JLPC2119 Watchdog and Timer 1 Interrupt Test\n");

  T1PR = 0;			// Timer 1 increments every pclk
  T1MR0 = 58982400;		// Match every second
  T1MCR = 0x003;		// Interrupt and reset at match

  DISABLE_INTERRUPTS(IRQ);

  VICIntSelect &= ~(1 << INT_TIMER1);	// TIMER1 uses IRQ
  VICVectCntl[0] = 0x20 + INT_TIMER1;	// TIMER1 uses vector 0
  VICVectAddr[0] = Timer1ISR;		// Save ISR address
  VICIntEnable = 1 << INT_TIMER1;	// Enable TIMER1 interrupt

  ENABLE_INTERRUPTS(IRQ);

  T1TCR = 1;			// Start Timer 1

  WDTC = 73728000;		// 5 second watchdog timeout

  WDMOD = 0x03;			// Watchdog timer issues reset

  WDFEED = 0xAA;		// Start watchdog timer
  WDFEED = 0x55;

  for (;;)
    if (Timer1Flag)
    {
      Timer1Flag = FALSE;
      puts("Tick...");
      fflush(stdout);

      WDFEED = 0xAA;		// Reset watchdog timer
      WDFEED = 0x55;
    }
}
