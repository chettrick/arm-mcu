/* Simple bit twiddler test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef LPC1114FN28
  LPC_IOCON->PIO0_7 = 0xC0;			// PIO0.7 is GPIO

  LPC_IOCON->R_PIO1_0 = 0xC1;			// Configure PIO1 pins for GPIO
  LPC_IOCON->R_PIO1_1 = 0xC1;
  LPC_IOCON->R_PIO1_2 = 0xC1;
  LPC_IOCON->PIO1_4 = 0xC0;
  LPC_IOCON->PIO1_5 = 0xC0;
  LPC_IOCON->PIO1_6 = 0xC0;
  LPC_IOCON->PIO1_7 = 0xC0;
  LPC_IOCON->PIO1_8 = 0xC0;
  LPC_IOCON->PIO1_9 = 0xC0;

  LPC_GPIO0->DIR = 0x80;			// P0.7 is output
  LPC_GPIO1->DIR = 0x3F7;			// P1.0-P1.9 are outputs

  for (i = 0;; i++)
  {
    LPC_GPIO0->DATA = i >> 12;			// Flash LED
    LPC_GPIO1->DATA = i;
  }
#endif
}
