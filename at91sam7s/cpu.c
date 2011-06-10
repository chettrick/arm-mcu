/* CPU initialization functions for the AT91SAM7S ARM MCU */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

unsigned long int CPUFREQ = DEFAULT_CPU_FREQ;

void cpu_init(unsigned long int frequency)
{

/* Configure watchdog timer */

  *AT91C_WDTC_WDMR	= AT91C_WDTC_WDDIS;	// Disable watchdog timer for now

/* Configure clock generators for 18.432 MHz crystal, 96 MHz PLL clock, and 48 MHz master clock */

  *AT91C_CKGR_MOR	= 0x0000FF01;		// Enable main oscillator
  while (!(*AT91C_PMC_SR & AT91C_PMC_MOSCS)); 	// Wait for main oscillator startup

  *AT91C_CKGR_PLLR	= 0x10FA3F30;		// Configure PLL (USBDIV=2, MUL=250, PLLCOUNT=63, DIV=48)
  while (!(*AT91C_PMC_SR & AT91C_PMC_LOCK)); 	// Wait for PLL to lock

  *AT91C_PMC_MCKR	= AT91C_PMC_PRES_CLK_2;	// Master clock divider is 2
  while (!(*AT91C_PMC_SR & AT91C_PMC_MCKRDY)); 	// Wait for master clock ready

  *AT91C_PMC_MCKR	= AT91C_PMC_PRES_CLK_2 | AT91C_PMC_CSS_PLL_CLK;	// Master clock source is PLL
  while (!(*AT91C_PMC_SR & AT91C_PMC_MCKRDY)); 	// Wait for master clock ready
}
