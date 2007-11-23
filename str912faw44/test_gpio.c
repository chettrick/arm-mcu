/* Simple bit twiddler test program */

// $Id: test_gpio.c,v 1.2 2007-11-23 12:31:34 cvs Exp $

#include <cpu.h>

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

  SCU_PCGR1 |= 0x00100000;	// Turn on GPIO6 clock
  SCU_PRR1  |= 0x00100000;	// Let GPIO6 out of reset

  SCU_GPIOOUT6  = 0x1555;	// P60 to P66 are GPIO outputs
  SCU_GPIOIN6   = 0x00;		// P60 to P66 are GPIO
  SCU_GPIOTYPE6 = 0x00;		// P60 to P66 are push pull

  GPIO6_SEL = 0x00;		// P60 to P66 are GPIO
  GPIO6_DIR = 0x7F;		// P60 to P66 are outputs

  for (i = 0;; i++)
  {
    GPIO6_DATA = i;
  }
}
