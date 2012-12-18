/* Abstract services for controlling LED's */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

// Initialize the LED's (to the off state)

void LEDS_initialize(void)
{
#ifdef LPC1114FN28
  LPC_IOCON->PIO0_7 = 0xC0;
  LPC_GPIO0->DIR |= 0x80;
#endif

  LEDS_set(0);						// Turn off all LEDs at startup
}

// Get LED states.  A 1 bit in the result indicates the LED is on.
// A 0 bit in the result indicates the LED is off.

unsigned long int LEDS_get(void)
{
  unsigned long int result = 0;

#ifdef LPC1114FN28
  result = LPC_GPIO0->MASKED_ACCESS[0x80] >> 7;
#endif

  return result;
}

// Set LED states.  A 1 bit in the mask indicates the LED should be turned on. 
// A 0 bit in the mask indicates the LED should be turned off.

void LEDS_set(unsigned long int mask)
{
#ifdef LPC1114FN28
  LPC_GPIO0->MASKED_ACCESS[0x80] = mask << 7;
#endif
}
