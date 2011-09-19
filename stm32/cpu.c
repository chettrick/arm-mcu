/* Initialize CPU core */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

void cpu_init(unsigned long int frequency)
{
  __use_custom_syscalls();

  SystemInit();
  SystemCoreClockUpdate();
}
