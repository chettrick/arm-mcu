/* Simple bit twiddler test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

  PINSEL2 = 0x00000000;         // Every P1 pin is a GPIO
  PINSEL3 = 0x00000000;

  FIO1MASK = 0x00000000;        // Every P1 pin is unmasked
  FIO1DIR = 0xFFFFFFFF;         // Every P1 pin is an output

  for (i = 0;; i++)
    FIO1PIN = i;
}
