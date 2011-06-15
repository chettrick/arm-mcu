/* Simple bit twiddler test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

void main(void)
{
  unsigned long i;

  cpu_init(DEFAULT_CPU_FREQ);

#ifndef NDEBUG
  serial_stdio(CONSOLE_PORT, 115200);	// For assert()
#endif

#ifdef OLIMEX_STM32_P103
  gpiopin_configure(GPIOPIN44, GPIOPIN_OUTPUT);

  for (i = 0;; i++)
  {
    GPIOPIN44OUT = i >> 20;
  }
#endif

#ifdef STM32_VALUE_LINE_DISCOVERY
  gpiopin_configure(GPIOPIN40, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN41, GPIOPIN_OUTPUT);

  for (i = 0;; i++)
  {
    GPIOPIN40OUT = i >> 19;
    GPIOPIN41OUT = i >> 20;
  }
#endif
}
