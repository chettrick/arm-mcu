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
  gpiopin_configure(GPIOPIN50, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN52, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN53, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN55, GPIOPIN_OUTPUT);

  for (i = 0;; i++)
  {
    GPIOPIN50OUT = i >> 22;
    GPIOPIN52OUT = i >> 21;
    GPIOPIN53OUT = i >> 20;
    GPIOPIN55OUT = i >> 19;
  }
#endif

// Flash BlueBoard LPC1768-H test LED

#ifdef BLUEBOARD_LPC1768_H
  gpiopin_configure(GPIOPIN61, GPIOPIN_OUTPUT);

  for (i = 0;; i++)
    GPIOPIN61OUT = i >> 20;
#endif
}
