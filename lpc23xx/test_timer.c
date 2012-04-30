/* Simple timer interrupt test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <stdio.h>

_BEGIN_STD_C

volatile int TimerFlag = FALSE;

__attribute__ ((__interrupt__)) void Timer1ISR(void)
{
  TimerFlag = TRUE;
  T1IR = 0x01;
  VICVectAddr = 0;
}

_END_STD_C

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);
  serial_stdio(CONSOLE_PORT);

  puts("\033[H\033[2JLPC23xx Timer Interrupt Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s %s %s\n\n", CPUFREQ, __COMPILER__, __VERSION__, __ABI__);

/* Configure LED(s) */

  LEDS_initialize();
  LEDS_set(LED2|LED4|LED6|LED8);

/* Configure timer 1 to interrupt once every second */

  T1TCR = 2;			// Reset timer 1
  T1TCR = 0;			// Release timer 1 reset
  T1PR = 0;			// Timer 1 precaler trips every PCLK
  T1CTCR = 0;			// Timer 1 increments every PCLK
  T1MR0 = CPUFREQ/4;		// Match every second
  T1MCR = 3;			// Interrupt and reset on match

/* Configure timer 1 interrupt */

  DISABLE_INTERRUPTS(IRQ);

  VICIntSelect &= ~(1 << INT_TIMER1);		// Timer 1 uses IRQ
  VICVectPriority5 = 0;
  VICVectAddr5 = (unsigned long int) Timer1ISR;	// Timer 1 ISR address
  VICIntEnable = 1 << INT_TIMER1;		// Enable timer 1 interrupt

  ENABLE_INTERRUPTS(IRQ);

  T1TCR = 1;			// Start timer 1

/* Start watchdog timer */

#ifndef DISABLE_WATCHDOG
  WDCLKSEL = 0x01;		// Watchdog timer runs on PCLK
  WDTC = CPUFREQ/16*5;		// 5 second watchdog timeout
  WDMOD = 0x03;			// Watchdog timer issues reset

  DISABLE_INTERRUPTS(IRQ);
  WDFEED = 0xAA;		// Start watchdog timer
  WDFEED = 0x55;
  ENABLE_INTERRUPTS(IRQ);
#endif

  for (;;)
    if (TimerFlag)
    {
      TimerFlag = FALSE;

      puts("Tick...");
      fflush(stdout);

      LEDS_set(~LEDS_get());

#ifndef DISABLE_WATCHDOG
      DISABLE_INTERRUPTS(IRQ);
      WDFEED = 0xAA;		// Reset watchdog timer
      WDFEED = 0x55;
      ENABLE_INTERRUPTS(IRQ);
#endif
    }
}
