/* Simple timer interrupt test program */

// $Id: test_timer1.c,v 1.2 2008-01-14 11:13:38 cvs Exp $

#include <conio.h>
#include <cpu.h>
#include <stdio.h>

#define TRUE	1
#define	FALSE	0

volatile int Timer1Flag = FALSE;

__attribute__ ((__interrupt__)) void Timer1ISR(void)
{
  static int ticks = 0;

  if (++ticks == 10)
  {
    ticks = 0;
    Timer1Flag = TRUE;
  }

  TIM1_SR = 0x0000;		// Clear OCF1
  TIM1_CNTR = 0x0000;		// Reset counter
  VIC0_VAR = 0;			// Signal end of interrupt
}

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);
  conio_init(0, 19200);

  puts("\033[H\033[2JSTR912FA Timer 1 Interrupt Test\n");

/* Configure timer 1 to interrupt 10 times a second */

  SCU_PCGR1 |= 0x0001;		// Enable timer 1 peripheral clock
  SCU_PRR1 |= 0x0001;		// Let timer 1 out of reset
  TIM1_CNTR = 0x0000;		// Reset counter
  TIM1_CR2 = 0x40FF;		// Prescale=256, output compare 1 interupt enabled
  TIM1_OC1R = 37496;		// 10 ticks per second
  TIM1_CR1 = 0x8000;		// Enable timer 1

/* Configure timer 1 interrupt */

  DISABLE_INTERRUPTS(IRQ);

  SCU_PCGR0 |= 0x0020;				// Enable VIC peripheral clock
  SCU_PRR0 |= 0x0020;				// Let VIC out of reset
  VIC0_INTSR &= ~(1 << INT_TIMER1);		// Timer 1 uses IRQ
  VIC0_VC0R = 0x0020 + INT_TIMER1;		// Timer 1 uses vector 0
  VIC0_VA0R = (unsigned long) Timer1ISR;	// Timer 1 ISR address
  VIC0_INTER |= 1 << INT_TIMER1;		// Enable timer 1 interrupt

  ENABLE_INTERRUPTS(IRQ);

/* Trivial main loop */

  for (;;)
    if (Timer1Flag)
    {
      Timer1Flag = FALSE;
      puts("Tick...");
      fflush(stdout);
    }
}
