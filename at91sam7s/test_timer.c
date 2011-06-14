/* Simple timer interrupt test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <stdio.h>

#include "aic.h"
#include "pit.h"

#define TRUE	1
#define	FALSE	0

volatile int TimerCounter = 0;
volatile int TimerFlag = FALSE;

__attribute__ ((__interrupt__)) void TimerISR(void)
{
  if (++TimerCounter == 10)
  {
    TimerCounter = 0;
    TimerFlag = TRUE;
  }

  *AT91C_AIC_EOICR = *AT91C_PITC_PIVR;	// Acknowledge interrupt
}

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);
  serial_stdio(CONSOLE_PORT, 115200);

/* Display startup banner */

  puts("\033[H\033[2JAT91SAM7S Timer Interrupt Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", CPUFREQ, __VERSION__);

/* Configure LED(s) */

  LEDS_initialize();
  LEDS_set(LED2|LED4|LED6|LED8);

/* Configure timer to interrupt 10 times a second */

  PIT_Init(100000, CPUFREQ/1000000);
  PIT_EnableIT();
  PIT_Enable();

/* Configure timer interrupt */

  AIC_ConfigureIT(AT91C_ID_SYS, AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL, TimerISR);
  AIC_EnableIT(AT91C_ID_SYS);

  for (;;)
  {
    if (TimerFlag)
    {
      TimerFlag = FALSE;

      puts("Tick...");
      fflush(stdout);

      LEDS_set(~LEDS_get());
    }
  }
}
