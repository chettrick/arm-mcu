/* Simple timer interrupt test program */

// $Id: test_timer1.c,v 1.7 2007-10-10 03:47:49 cvs Exp $

#include <conio.h>
#include <cpu.h>
#include <stdio.h>
#include <string.h>

#define TRUE	1
#define	FALSE	0

volatile int Timer1Flag = FALSE;

__attribute__ ((__interrupt__)) void Timer1ISR(void)
{
  Timer1Flag = TRUE;
  T1IR = 0x01;
  VICVectAddr = 0;
}

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);
  conio_init(U0RBR, 19200);

  puts("\033[H\033[2JLPC2119 Watchdog and Timer 1 Interrupt Test\n");

  T1PR = 0;			// Timer 1 increments every pclk
  T1MR0 = CPUFREQ;		// Match every second
  T1MCR = 0x003;		// Interrupt and reset at match

  DISABLE_INTERRUPTS(IRQ);

  VICIntSelect &= ~(1 << INT_TIMER1);	// TIMER1 uses IRQ
  VICVectCntl0 = 0x20 + INT_TIMER1;	// TIMER1 uses vector 0
  VICVectAddr0 = (unsigned long) Timer1ISR; // Save ISR address
  VICIntEnable = 1 << INT_TIMER1;	// Enable TIMER1 interrupt

  ENABLE_INTERRUPTS(IRQ);

  T1TCR = 1;			// Start Timer 1

  WDTC = CPUFREQ/4*5;		// 5 second watchdog timeout

#ifndef DISABLE_WATCHDOG
  WDMOD = 0x03;			// Watchdog timer issues reset

  DISABLE_INTERRUPTS(IRQ);
  WDFEED = 0xAA;		// Start watchdog timer
  WDFEED = 0x55;
  ENABLE_INTERRUPTS(IRQ);
#endif

  for (;;)
    if (Timer1Flag)
    {
      Timer1Flag = FALSE;
      puts("Tick...");
      fflush(stdout);

#ifndef DISABLE_WATCHDOG
      DISABLE_INTERRUPTS(IRQ);
      WDFEED = 0xAA;		// Reset watchdog timer
      WDFEED = 0x55;
      ENABLE_INTERRUPTS(IRQ);
#endif
    }
}
