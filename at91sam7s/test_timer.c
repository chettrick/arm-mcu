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

  puts("\033[H\033[2JAT91SAM7S Timer Interrupt Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", CPUFREQ, __VERSION__);

/* Configure LED */

#ifdef BOARD_OLIMEX_SAM7_P256
#define LED1            18
#define LED2            17

  *AT91C_PMC_PCER       = 0x00000004;   // Enable Port A peripheral clock

  *AT91C_PIOA_PER       = 1 << LED1;    // LED1 pin is GPIO
  *AT91C_PIOA_PPUDR     = 1 << LED1;    // LED1 pin does not need internal pullup
  *AT91C_PIOA_OER       = 1 << LED1;    // LED1 pin is output
  *AT91C_PIOA_MDER      = 1 << LED1;    // LED1 pin is open drain output
  *AT91C_PIOA_SODR	= 1 << LED1;	// LED1 pin is off
#endif

/* Configure timer to interrupt 10 times a second */

  PIT_Init(100000, CPUFREQ/1000000);
  PIT_EnableIT();
  PIT_Enable();

/* Configure timer interrupt */

  AIC_ConfigureIT(AT91C_ID_SYS, AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL, TimerISR);
  AIC_EnableIT(AT91C_ID_SYS);

  for (;;)
    if (TimerFlag)
    {
      TimerFlag = FALSE;

      puts("Tick...");
      fflush(stdout);

#ifdef BOARD_OLIMEX_SAM7_P256
      if (*AT91C_PIOA_PDSR & (1 << LED1))
        *AT91C_PIOA_CODR = 1 << LED1;
      else
        *AT91C_PIOA_SODR = 1 << LED1;
#endif
    }
}
