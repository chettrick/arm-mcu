/* Simple bit twiddler test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef OLIMEX_LPC_P2378
#define LEDMASK (1 << 19)
  PCLKSEL1 = 0x00000004;	// GPIO peripheral clock is CCLK/1

  FIO1MASK &= ~LEDMASK;		// Unmask LED pin
  FIO1DIR |= LEDMASK;		// Make output LED pin

  for (i = 0;; i++)
    FIO1PIN = i;
#endif

#ifdef MBED_LPC2368
#define LEDMASK ((1 << 18)|(1 << 20)|(1 << 21)|(1 << 23))
  PCLKSEL1 = 0x00000004;	// GPIO peripheral clock is CCLK/1

  FIO1MASK &= ~LEDMASK;		// Unmask LED pins
  FIO1DIR |= LEDMASK;		// Make output LED pins

  for (i = 0;; i++)
    FIO1PIN = i;
#endif
}
