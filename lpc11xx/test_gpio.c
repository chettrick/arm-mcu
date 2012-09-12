/* Simple bit twiddler test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 6);	// Enable GPIO

#ifdef LPC1114FN28
  LPC_GPIO1->DIR = 0xFF;	// P1.0-P1.7 are outputs

  for (i = 0;; i++)
    LPC_GPIO1->DATA = i;
#endif
}
