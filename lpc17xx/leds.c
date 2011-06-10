/* Abstract services for controlling LED's */

// $Id$

#include <cpu.h>
#include <leds.h>

#ifdef MBED_LPC1768
#define MAX_LEDS	4
static const char LED_PINS[MAX_LEDS] = { 23, 21, 20, 18 };	// All are on GPIO1 pins
#endif

#ifdef BLUEBOARD_LPC1768_H
#define LED_PIN		29
#endif

// Initialize the LED's (to the off state)

void LEDS_initialize(void)
{
#ifdef MBED_LPC1768
  int i;

  for (i = 0; i < MAX_LEDS; i++)
  {
    LPC_GPIO1->FIOMASK &= ~(1 << LED_PINS[i]);
    LPC_GPIO1->FIODIR |= (1 << LED_PINS[i]);
  }
#endif

#ifdef BLUEBOARD_LPC1768_H
  LPC_GPIO1->FIOMASK &= ~(1 << LED_PIN);
  LPC_GPIO1->FIODIR |= (1 << LED_PIN);
#endif

  LEDS_set(0);						// Turn off all LEDs at startup
}

// Get LED states.  A 1 bit in the result indicates the LED is on.
// A 0 bit in the result indicates the LED is off.

unsigned long int LEDS_get(void)
{
  unsigned long int result = 0;

#ifdef MBED_LPC1768
  int i;

  for (i = 0; i < MAX_LEDS; i++)
  {
    if (LPC_GPIO1->FIOPIN & (1 << LED_PINS[i]))
      result |= (1 << i);
  }
#endif

#ifdef BLUEBOARD_LPC1768_H
  if (LPC_GPIO1->FIOPIN & (1 << LED_PIN))
    result = 1;
#endif

  return result;
}

// Set LED states.  A 1 bit in the mask indicates the LED should be turned on. 
// A 0 bit in the mask indicates the LED should be turned off.

void LEDS_set(unsigned long int mask)
{
#ifdef MBED_LPC1768
  int i;

  for (i = 0; i < MAX_LEDS; i++)
  {
    if (mask & 0x01)
      LPC_GPIO1->FIOSET = (1 << LED_PINS[i]);
    else
      LPC_GPIO1->FIOCLR = (1 << LED_PINS[i]);

    mask >>= 1;
  }
#endif

#ifdef BLUEBOARD_LPC1768_H
  if (mask & 0x01)
    LPC_GPIO1->FIOSET = (1 << LED_PIN);
  else
    LPC_GPIO1->FIOCLR = (1 << LED_PIN);
#endif
}
