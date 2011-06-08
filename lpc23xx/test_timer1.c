/* Simple timer interrupt test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <stdio.h>

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
  serial_stdio(CONSOLE_PORT, 115200);

  puts("\033[H\033[2JLPC23xx Watchdog and Timer 1 Interrupt Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", CPUFREQ, __VERSION__);

/* Configure LED(s) */

#ifdef BOARD_OLIMEX_LPC_P2378
#define LEDMASK (1 << 19)
  PCLKSEL1 = 0x00000004;	// GPIO peripheral clock is CCLK/1

  FIO1MASK &= ~LEDMASK;		// Unmask LED pin
  FIO1DIR |= LEDMASK;		// Make output LED pin
#endif

#ifdef BOARD_MBED_LPC2368
#define LEDMASK ((1 << 18)|(1 << 20)|(1 << 21)|(1 << 23))
  PCLKSEL1 = 0x00000004;	// GPIO peripheral clock is CCLK/1

  FIO1MASK &= ~LEDMASK;		// Unmask LED pins
  FIO1DIR |= LEDMASK;		// Make output LED pins
#endif

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
  VICVectAddr5 = (unsigned long) Timer1ISR;	// Timer 1 ISR address
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
    if (Timer1Flag)
    {
      Timer1Flag = FALSE;

#ifdef BOARD_OLIMEX_LPC_P2378
      FIO1PIN = ~FIO1PIN;	// Toggle LED
#endif

#ifdef BOARD_MBED_LPC2368
      FIO1PIN = ~FIO1PIN;	// Toggle LED
#endif

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
