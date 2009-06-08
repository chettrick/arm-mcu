/* Initialize CPU core */

// $Id$

#include <cpu.h>

unsigned long int CPUFREQ;

void cpu_init(unsigned long int frequency)
{
  CPUFREQ = DEFAULT_CPU_FREQ;	// Not currently changeable

  MAMCR = 2;			// MAM functions fully enabled

  VPBDIV = 0x01;		// pclk = cclk

  PLLCFG = (0x01 << 5) + 0x02;	// M=3, P=2
  PLLCON = 1;			// Enable PLL
  PLLFEED = 0xAA;
  PLLFEED = 0x55;

  while((PLLSTAT & 0x400) == 0);

  PLLCON = 3;			// Connect PLL
  PLLFEED = 0xAA;
  PLLFEED = 0x55;
}
