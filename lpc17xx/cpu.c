/* Initialize CPU core */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <system_LPC17xx.h>

void cpu_init(unsigned long int frequency)
{
  SystemInit();
  SystemCoreClockUpdate();
}
