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
  gpiopin_configure(GPIOPIN61, GPIOPIN_OUTPUT);
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
