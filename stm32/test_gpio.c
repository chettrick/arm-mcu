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

#ifdef OLIMEX_STM32_P107
  gpiopin_configure(GPIOPIN38, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN39, GPIOPIN_OUTPUT);

  for (i = 0;; i++)
  {
    GPIOPIN38OUT = i >> 20;
    GPIOPIN39OUT = i >> 21;
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

#ifdef W5200E01_M3
  gpiopin_configure(GPIOPIN0, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN1, GPIOPIN_OUTPUT);

  for (i = 0;; i++)
  {
    GPIOPIN0OUT = i >> 19;
    GPIOPIN1OUT = i >> 20;
  }
#endif
}
