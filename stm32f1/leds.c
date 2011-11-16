/* Abstract services for controlling LED's */

// $Id$

#include <cpu.h>

// Initialize the LED's (to the off state)

void LEDS_initialize(void)
{
#ifdef OLIMEX_STM32_P103
  gpiopin_configure(GPIOPIN44, GPIOPIN_OUTPUT);
#endif

#ifdef OLIMEX_STM32_P107
  gpiopin_configure(GPIOPIN38, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN39, GPIOPIN_OUTPUT);
#endif

#ifdef STM32_VALUE_LINE_DISCOVERY
  gpiopin_configure(GPIOPIN40, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN41, GPIOPIN_OUTPUT);
#endif

#ifdef W5200E01_M3
  gpiopin_configure(GPIOPIN0, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN1, GPIOPIN_OUTPUT);
#endif

  LEDS_set(0);						// Turn off all LEDs at startup
}

// Get LED states.  A 1 bit in the result indicates the LED is on.
// A 0 bit in the result indicates the LED is off.

unsigned long int LEDS_get(void)
{
  unsigned long int result = 0;

#ifdef OLIMEX_STM32_P103
  result += !GPIOPIN44IN;
#endif

#ifdef OLIMEX_STM32_P107
  result += GPIOPIN38IN;
  result += GPIOPIN39IN << 1;
#endif

#ifdef STM32_VALUE_LINE_DISCOVERY
  result += GPIOPIN40IN;
  result += GPIOPIN41IN << 1;
#endif

#ifdef W5200E01_M3
  result += !GPIOPIN0IN;
  result += !GPIOPIN1IN << 1;
#endif

  return result;
}

// Set LED states.  A 1 bit in the mask indicates the LED should be turned on. 
// A 0 bit in the mask indicates the LED should be turned off.

void LEDS_set(unsigned long int mask)
{
#ifdef OLIMEX_STM32_P103
  GPIOPIN44OUT = ~mask;
#endif

#ifdef OLIMEX_STM32_P107
  GPIOPIN38OUT = mask;
  GPIOPIN39OUT = mask >> 1;
#endif

#ifdef STM32_VALUE_LINE_DISCOVERY
  GPIOPIN40OUT = mask;
  GPIOPIN41OUT = mask >> 1;
#endif

#ifdef W5200E01_M3
  GPIOPIN0OUT = ~mask;
  GPIOPIN1OUT = ~mask >> 1;
#endif
}
