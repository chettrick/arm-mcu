/* Simple bit twiddler test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

#ifndef NDEBUG
  serial_stdio(CONSOLE_PORT, 115200);	// For assert()
#endif

#ifdef EFM32_G8XX_STK
  gpiopin_configure(32, GPIOPIN_OUTPUT);
  gpiopin_configure(33, GPIOPIN_OUTPUT);
  gpiopin_configure(34, GPIOPIN_OUTPUT);
  gpiopin_configure(35, GPIOPIN_OUTPUT);

  for (i = 0;; i++)
  {
    GPIOPIN32OUT = i >> 16;
    GPIOPIN33OUT = i >> 17;
    GPIOPIN34OUT = i >> 18;
    GPIOPIN35OUT = i >> 19;
  }
#endif
}
