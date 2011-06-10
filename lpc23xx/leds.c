/* Abstract services for controlling LED's */

// $Id$

#include <cpu.h>
#include <leds.h>

#ifdef MBED_LPC2368
#define MAX_LEDS	4
static const char LED_PINS[MAX_LEDS] = { 23, 21, 20, 18 };	// All are on GPIO1 pins
#endif

#ifdef OLIMEX_LPC_P2378
#define LED_PIN		19
#endif

// Initialize the LED's (to the off state)

void LEDS_initialize(void)
{
#ifdef MBED_LPC2368
  int i;

  for (i = 0; i < MAX_LEDS; i++)
  {
    FIO1MASK &= ~(1 << LED_PINS[i]);
    FIO1DIR |= (1 << LED_PINS[i]);
  }
#endif

#ifdef OLIMEX_LPC_P2378
  FIO1MASK &= ~(1 << LED_PIN);
  FIO1DIR |= (1 << LED_PIN);
#endif

  LEDS_set(0);						// Turn off all LEDs at startup
}

// Get LED states.  A 1 bit in the result indicates the LED is on.
// A 0 bit in the result indicates the LED is off.

unsigned long int LEDS_get(void)
{
  unsigned long int result = 0;

#ifdef MBED_LPC2368
  int i;

  for (i = 0; i < MAX_LEDS; i++)
  {
    if (FIO1PIN & (1 << LED_PINS[i]))
      result |= (1 << i);
  }
#endif

#ifdef OLIMEX_LPC_P2378
  if (FIO1PIN & (~(1 << LED_PIN)))
    result = 1;
#endif

  return result;
}

// Set LED states.  A 1 bit in the mask indicates the LED should be turned on. 
// A 0 bit in the mask indicates the LED should be turned off.

void LEDS_set(unsigned long int mask)
{
#ifdef MBED_LPC2368
  int i;

  for (i = 0; i < MAX_LEDS; i++)
  {
    if (mask & 0x01)
      FIO1SET = (1 << LED_PINS[i]);
    else
      FIO1CLR = (1 << LED_PINS[i]);

    mask >>= 1;
  }
#endif

#ifdef OLIMEX_LPC_P2378
  if (mask & 0x01)
    FIO1CLR = (1 << LED_PIN);
  else
    FIO1SET = (1 << LED_PIN);
#endif
}
