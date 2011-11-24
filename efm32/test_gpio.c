/* Simple bit twiddler test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef EFM32_G8XX_STK
  gpiopin_configure(25, GPIOPIN_INPUT);
  gpiopin_configure(26, GPIOPIN_INPUT);
  gpiopin_configure(32, GPIOPIN_OUTPUT);
  gpiopin_configure(33, GPIOPIN_OUTPUT);
  gpiopin_configure(34, GPIOPIN_OUTPUT);
  gpiopin_configure(35, GPIOPIN_OUTPUT);

  for (i = 0;; i++)
  {
    // Speed up flashing if PB0 is pressed

    if (!GPIOPIN25IN)
    {
      GPIOPIN32OUT = i >> 16;
      GPIOPIN33OUT = i >> 17;
      GPIOPIN34OUT = i >> 18;
      GPIOPIN35OUT = i >> 19;
    }

    // Turn off LED's if PB1 is pressed

    else if (!GPIOPIN26IN)
    {
      GPIOPIN32OUT = 0;
      GPIOPIN33OUT = 0;
      GPIOPIN34OUT = 0;
      GPIOPIN35OUT = 0;
    }

    // Normal flashing

    else
    {
      GPIOPIN32OUT = i >> 17;
      GPIOPIN33OUT = i >> 18;
      GPIOPIN34OUT = i >> 19;
      GPIOPIN35OUT = i >> 20;
    }
  }
#endif
}
