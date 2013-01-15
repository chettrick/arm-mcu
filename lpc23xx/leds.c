/* Abstract services for controlling LED's */

// $Id$

// Copyright (C)2013, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification,are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// * Neither the name of Munts AM Corp. nor the names of its contributors may
//   be used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

static const char revision[] = "$Id$";

#include <cpu.h>

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
  if (!(FIO1PIN & (1 << LED_PIN)))
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
