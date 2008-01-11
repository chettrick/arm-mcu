/* CPU initialization functions for the AT91SAM7S256 */

// $Id: cpu.c,v 1.1 2008-01-11 10:58:59 cvs Exp $

#include <cpu.h>

unsigned long int CPUFREQ;

void cpu_init(unsigned long int frequency)
{
  CPUFREQ = DEFAULT_CPU_FREQ;			// Not currently changeable

/* Configure watchdog timer */

  *AT91C_WDTC_WDMR	= AT91C_WDTC_WDDIS;	// Disable watchdog timer for now

/* Configure clock generators for 18.432 MHz crystal, 96 MHz PLL clock, and 48 MHz master clock */

  *AT91C_CKGR_MOR	= 0x0000FF01;		// Enable main oscillator
  while (!(*AT91C_PMC_SR & AT91C_PMC_MOSCS)); 	// Wait for main oscillator startup

  *AT91C_CKGR_PLLR	= 0x00480A0E;		// Configure PLL (USBDIV=2, MUL=72, DIV=14)
  while (!(*AT91C_PMC_SR & AT91C_PMC_LOCK)); 	// Wait for PLL to lock

  *AT91C_PMC_MCKR	= AT91C_PMC_PRES_CLK_2;	// Master clock divider is 2
  while (!(*AT91C_PMC_SR & AT91C_PMC_MCKRDY)); 	// Wait for master clock ready

  *AT91C_PMC_MCKR	= AT91C_PMC_PRES_CLK_2 | AT91C_PMC_CSS_PLL_CLK;	// Master clock source is PLL
  while (!(*AT91C_PMC_SR & AT91C_PMC_MCKRDY)); 	// Wait for master clock ready
}
