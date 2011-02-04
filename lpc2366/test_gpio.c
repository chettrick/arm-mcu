/* Simple bit twiddler test program */

// $Id$

#include <cpu.h>

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

/* Configure P0 pins */

  PCLKSEL1 = 0x00000004;	// GPIO peripheral clock is CCLK/1

#ifdef BOARD_OLIMEX_LPC_P2378
  PINSEL0 = 0x00000000;		// Every P0 pin is a GPIO
  PINSEL1 = 0x00000000;

  FIO0MASK = 0x00000000;	// Every P0 pin is unmasked
  FIO0DIR = 0xFFFFFFFF;		// Every P0 pin is an output

  for (i = 0;; i++)
    FIO0PIN = i;
#endif

#ifdef BOARD_MBED_LPC2368
  PINSEL2 = 0x00000000;         // Every P1 pin is a GPIO
  PINSEL3 = 0x00000000;

  FIO1MASK = 0x00000000;        // Every P1 pin is unmasked
  FIO1DIR = 0xFFFFFFFF;         // Every P1 pin is an output

  for (i = 0;; i++)
    FIO1PIN = i;
#endif
}
