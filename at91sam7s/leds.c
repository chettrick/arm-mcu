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

#ifdef OLIMEX_SAM7_P256
#define MAX_LEDS	2

static const unsigned char LED_PINS[MAX_LEDS] = { 18, 17 };
#endif

// Initialize the LED's (to the off state)

void LEDS_initialize(void)
{
#ifdef OLIMEX_SAM7_P256
  int i;

  *AT91C_PMC_PCER	= 0x00000004;		// Enable Port A peripheral clock

  for (i = 0; i < MAX_LEDS; i++)
  {
    *AT91C_PIOA_PER	= 1 << LED_PINS[i];	// LED pin is GPIO
    *AT91C_PIOA_PPUDR	= 1 << LED_PINS[i];	// LED pin does not need internal pullup
    *AT91C_PIOA_OER	= 1 << LED_PINS[i];	// LED pin is output
    *AT91C_PIOA_OWER	= 1 << LED_PINS[i];	// LED pin is synchronous output
    *AT91C_PIOA_MDER	= 1 << LED_PINS[i];	// LED pin is open drain output
  } 
#endif

  LEDS_set(0);					// Turn off all LEDs at startup
}

// Get LED states.  A 1 bit in the result indicates the LED is on.
// A 0 bit in the result indicates the LED is off.

unsigned long int LEDS_get(void)
{
  unsigned long int result = 0;

#ifdef OLIMEX_SAM7_P256
  int i;

  for (i = 0; i < MAX_LEDS; i++)
  {
    if (!(*AT91C_PIOA_PDSR & (1 << LED_PINS[i])))
      result |= (1 << i);
  }
#endif

  return result;
}

// Set LED states.  A 1 bit in the mask indicates the LED should be turned on. 
// A 0 bit in the mask indicates the LED should be turned off.

void LEDS_set(unsigned long int mask)
{
#ifdef OLIMEX_SAM7_P256
  int i;

  for (i = 0; i < MAX_LEDS; i++)
  {
    if (mask & 0x01)
      *AT91C_PIOA_CODR = 1 << LED_PINS[i];	// Turn LED on
    else
      *AT91C_PIOA_SODR = 1 << LED_PINS[i];	// Turn LED off

    mask >>= 1;
  }
#endif
}
