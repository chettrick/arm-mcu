/* Simple bit twiddler test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

// Flash MBED-LPC1768 LED's

#ifdef MBED_LPC1768
#define LEDMASK	((1 << 18)|(1 << 20)|(1 << 21)|(1 << 23))

  LPC_GPIO1->FIOMASK &= ~LEDMASK;
  LPC_GPIO1->FIODIR |= LEDMASK;

  for (i = 0;; i++)
    LPC_GPIO1->FIOPIN = i;
#endif

// Flash BlueBoard LPC1768-H test LED

#ifdef BLUEBOARD_LPC1768_H
#define LEDMASK	((1 << 29))

  LPC_GPIO1->FIOMASK &= ~LEDMASK;
  LPC_GPIO1->FIODIR |= LEDMASK;

  for (i = 0;; i++)
    LPC_GPIO1->FIOPIN = i << 7;
#endif
}
