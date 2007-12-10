/* Initialize CPU core */

// $Id: cpu.c,v 1.4 2007-12-10 10:20:15 cvs Exp $

#include <cpu.h>
#include <stdio.h>
#include <string.h>

unsigned long int CPUFREQ;

void cpu_init(unsigned long int frequency)
{
  CPUFREQ = DEFAULT_CPU_FREQ;	// Not currently changeable

/* Initialize MAM--See Errata MAM.1 */

  MAMCR = 1;			// MAM functions fully enabled
  MAMTIM = 3;			// 3 CPU clocks per fetch cycle

/* Configure clock generators--See Errata PLL.1 and Flash.1 */

  SCS = 0x00000021;		// Turn on main oscillator, fast GPIO
  while (!(SCS & (1 << 6)));	// Wait for main oscillator startup

  CLKSRCSEL = 1;		// PLL source is main oscillator

  PLLCFG = 11;			// N=1, M=12 (Fin=12 MHz, Fref=12 MHz, Fcco=288 MHz)
  PLLCON = 1;			// Enable PLL
  PLLFEED = 0xAA;
  PLLFEED = 0x55;

  while (!(PLLSTAT & (1 << 26))); // Wait for PLL lock

  CCLKCFG = 5;			// CPU clock is Fcco/4 (48 MHz)
  USBCLKCFG = 5;		// USB clock is Fcco/6 (48 MHz)

  PLLCON = 3;			// Connect PLL
  PLLFEED = 0xAA;
  PLLFEED = 0x55;
}
