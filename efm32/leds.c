/* Abstract services for controlling LED's */

// $Id$

#include <cpu.h>
#include <leds.h>

// Initialize the LED's (to the off state)

void LEDS_initialize(void)
{
#ifdef EFM32_G8XX_STK
  gpiopin_configure(32, GPIOPIN_OUTPUT);
  gpiopin_configure(33, GPIOPIN_OUTPUT);
  gpiopin_configure(34, GPIOPIN_OUTPUT);
  gpiopin_configure(35, GPIOPIN_OUTPUT);
#endif

  LEDS_set(0);						// Turn off all LEDs at startup
}

// Get LED states.  A 1 bit in the result indicates the LED is on.
// A 0 bit in the result indicates the LED is off.

unsigned long int LEDS_get(void)
{
  unsigned long int result = 0;

#ifdef EFM32_G8XX_STK
  result += GPIOPIN32OUT;
  result += GPIOPIN33OUT << 1;
  result += GPIOPIN34OUT << 2;
  result += GPIOPIN35OUT << 3;
#endif

  return result;
}

// Set LED states.  A 1 bit in the mask indicates the LED should be turned on. 
// A 0 bit in the mask indicates the LED should be turned off.

void LEDS_set(unsigned long int mask)
{
#ifdef EFM32_G8XX_STK
  GPIOPIN32OUT = mask;
  GPIOPIN33OUT = mask >> 1;
  GPIOPIN34OUT = mask >> 2;
  GPIOPIN35OUT = mask >> 3;
#endif
}
