/* Abstract services for controlling LED's */

// $Id$

// Copyright (C)2013, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
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
