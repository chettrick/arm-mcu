/* Simple bit twiddler test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef LPC1114FN28
  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);	// Enable IOCON

  LPC_IOCON->R_PIO1_0 = 0xC1;
  LPC_IOCON->R_PIO1_1 = 0xC1;
  LPC_IOCON->R_PIO1_2 = 0xC1;
  LPC_IOCON->PIO1_4 = 0xC0;
  LPC_IOCON->PIO1_5 = 0xC0;
  LPC_IOCON->PIO1_6 = 0xC0;
  LPC_IOCON->PIO1_7 = 0xC0;
  LPC_IOCON->PIO1_8 = 0xC0;
  LPC_IOCON->PIO1_9 = 0xC0;

  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 6);	// Enable GPIO

  LPC_GPIO1->DIR = 0x3F7;	// P1.0-P1.9 are outputs

  for (i = 0;; i++)
    LPC_GPIO1->DATA = i;
#endif
}
