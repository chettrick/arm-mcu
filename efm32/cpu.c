/* Initialize CPU core */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <system_efm32.h>

unsigned long int CPUFREQ;

void cpu_init(unsigned long int frequency)
{
  CHIP_Init();			// Fix chip errata

  SystemInit();
  SystemCoreClockUpdate();

  CPUFREQ = SystemCoreClock;	// Not currently changeable
}
