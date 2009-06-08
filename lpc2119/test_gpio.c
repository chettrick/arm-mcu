/* Simple bit twiddler test program */

// $Id$

#include <cpu.h>

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

  PINSEL0 = 0x00000000;	// Every pin is a GPIO
  PINSEL1 = 0x00000000;
  PINSEL2 = 0x00000030;

  IO0DIR = 0xFFFFFFFF;	// Every pin is an output
  IO1DIR = 0xFFFFFFFF;

  for (i = 0;; i++)
  {
    IO0PIN = i;
    IO1PIN = i;
  }
}
