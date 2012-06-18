/* Initialize CPU core */

// $Id: cpu.c 3016 2011-09-19 10:44:24Z svn $

static const char revision[] = "$Id: cpu.c 3016 2011-09-19 10:44:24Z svn $";

#include <cpu.h>

void cpu_init(unsigned long int frequency)
{
  SystemInit();
  SystemCoreClockUpdate();
}
