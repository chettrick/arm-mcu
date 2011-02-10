/* Initialize CPU core */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

unsigned long int CPUFREQ;

void cpu_init(unsigned long int frequency)
{
  CPUFREQ = DEFAULT_CPU_FREQ;	// Not currently changeable

  SystemInit();
}
