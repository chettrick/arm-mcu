/* Abstract services for controlling LED's */

// $Id: leds.c 2988 2011-09-06 08:28:59Z svn $

static const char revision[] = "$Id: cpu.c 3016 2011-09-19 10:44:24Z svn $";

#include <cpu.h>

// Initialize the LED's (to the off state)

void LEDS_initialize(void)
{
#ifdef STM32F4_DISCOVERY
  gpiopin_configure(GPIOPIN60, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN61, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN62, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN63, GPIOPIN_OUTPUT);
#endif

  LEDS_set(0);						// Turn off all LEDs at startup
}

// Get LED states.  A 1 bit in the result indicates the LED is on.
// A 0 bit in the result indicates the LED is off.

unsigned long int LEDS_get(void)
{
  unsigned long int result = 0;

#ifdef STM32F4_DISCOVERY
  result += GPIOPIN60IN;
  result += GPIOPIN61IN << 1;
  result += GPIOPIN62IN << 2;
  result += GPIOPIN63IN << 3;
#endif

  return result;
}

// Set LED states.  A 1 bit in the mask indicates the LED should be turned on. 
// A 0 bit in the mask indicates the LED should be turned off.

void LEDS_set(unsigned long int mask)
{
#ifdef STM32F4_DISCOVERY
  GPIOPIN60OUT = mask;
  GPIOPIN61OUT = mask >> 1;
  GPIOPIN62OUT = mask >> 2;
  GPIOPIN63OUT = mask >> 3;
#endif
}
