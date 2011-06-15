/* Abstract services for controlling LED's */

// $Id$

#include <cpu.h>

// Initialize the LED's (to the off state)

void LEDS_initialize(void)
{
#ifdef MBED_LPC1768
  gpiopin_configure(GPIOPIN50, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN52, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN53, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN55, GPIOPIN_OUTPUT);
#endif

#ifdef BLUEBOARD_LPC1768_H
  gpiopin_configure(GPIOPIN61, GPIOPIN_OUTOUT);
#endif

  LEDS_set(0);						// Turn off all LEDs at startup
}

// Get LED states.  A 1 bit in the result indicates the LED is on.
// A 0 bit in the result indicates the LED is off.

unsigned long int LEDS_get(void)
{
  unsigned long int result = 0;

#ifdef MBED_LPC1768
  result += GPIOPIN55OUT;
  result += GPIOPIN53OUT << 1;
  result += GPIOPIN52OUT << 2;
  result += GPIOPIN50OUT << 3;
#endif

#ifdef BLUEBOARD_LPC1768_H
  result += GPIOPIN61IN;
#endif

  return result;
}

// Set LED states.  A 1 bit in the mask indicates the LED should be turned on. 
// A 0 bit in the mask indicates the LED should be turned off.

void LEDS_set(unsigned long int mask)
{
#ifdef MBED_LPC1768
  GPIOPIN55OUT = mask;
  GPIOPIN53OUT = mask >> 1;
  GPIOPIN52OUT = mask >> 2;
  GPIOPIN50OUT = mask >> 3;
#endif

#ifdef BLUEBOARD_LPC1768_H
  GPIOPIN61OUT = mask;
#endif
}
