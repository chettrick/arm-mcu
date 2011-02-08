/* Initialize CPU core */

// $Id$

static const char cpu_revision[] = "$Id$";

#include <cpu.h>

unsigned long int CPUFREQ;

void cpu_init(unsigned long int frequency)
{
  CPUFREQ = DEFAULT_CPU_FREQ;	// Not currently changeable

/* Initialize MAM--See Errata MAM.1 */

#ifdef REVISION_A
  MAMCR = 1;			// MAM functions partially enabled
  MAMTIM = 3;			// 3 CPU clocks per fetch cycle
#else
  MAMCR = 2;			// MAM functions fully enabled
  MAMTIM = 4;			// CPU clocks per fetch cycle
#endif

/* Configure clock generators--See Errata PLL.1 and Flash.1 */

  SCS = 0x00000021;		// Turn on main oscillator, fast GPIO
  while (!(SCS & (1 << 6)));	// Wait for main oscillator startup

  CLKSRCSEL = 1;		// PLL source is main oscillator

  PLLCFG = 11;			// N=1, M=12 (Fin=12 MHz, Fref=12 MHz, Fcco=288 MHz)
  PLLCON = 1;			// Enable PLL
  PLLFEED = 0xAA;
  PLLFEED = 0x55;

  while (!(PLLSTAT & (1 << 26))); // Wait for PLL lock

#ifdef REVISION_A
  CCLKCFG = 5;			// CPU clock is Fcco/6 (48 MHz)
#else
  CCLKCFG = 3;			// CPU clock is Fcco/4 (72 MHz)
#endif
  USBCLKCFG = 5;		// USB clock is Fcco/6 (48 MHz)

  PLLCON = 3;			// Connect PLL
  PLLFEED = 0xAA;
  PLLFEED = 0x55;
}
