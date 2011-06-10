/* Abstract services for controlling LED's */

// $Id$

#include <cpu.h>
#include <leds.h>

// Initialize the LED's (to the off state)

void LEDS_initialize(void)
{
#ifdef EFM32_G8XX_STK
  /* Enable GPIO */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Configure GPIO port C 0-3 as LED control outputs */
  GPIO_PinModeSet(gpioPortC, 0, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortC, 1, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortC, 2, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortC, 3, gpioModePushPull, 1);
#endif

  LEDS_set(0);						// Turn off all LEDs at startup
}

// Get LED states.  A 1 bit in the result indicates the LED is on.
// A 0 bit in the result indicates the LED is off.

unsigned long int LEDS_get(void)
{
  unsigned long int result = 0;

#ifdef EFM32_G8XX_STK
  result = GPIO_PortOutGet(gpioPortC) & 0x0F;
#endif

  return result;
}

// Set LED states.  A 1 bit in the mask indicates the LED should be turned on. 
// A 0 bit in the mask indicates the LED should be turned off.

void LEDS_set(unsigned long int mask)
{
#ifdef EFM32_G8XX_STK
  GPIO_PortOutSetVal(gpioPortC, mask, 0xf);
#endif
}
