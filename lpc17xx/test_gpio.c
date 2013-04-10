/* Simple bit twiddler test program */

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

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

// Flash MBED-LPC1768 LED's

#ifdef MBED_LPC1768
  gpiopin_configure(GPIOPIN50, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN52, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN53, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN55, GPIOPIN_OUTPUT);

  for (i = 0;; i++)
  {
    GPIOPIN50OUT = i >> 22;
    GPIOPIN52OUT = i >> 21;
    GPIOPIN53OUT = i >> 20;
    GPIOPIN55OUT = i >> 19;
  }
#endif

// Flash BlueBoard LPC1768-H test LED

#ifdef BLUEBOARD_LPC1768_H
  gpiopin_configure(GPIOPIN61, GPIOPIN_OUTPUT);	// Test LED D8
  gpiopin_configure(GPIOPIN74, GPIOPIN_INPUT);	// Push button SW2

  for (i = 0;; i++)
  {
    // Flash faster if button is pressed

    if (!GPIOPIN74IN)
    {
      GPIOPIN61OUT = i >> 18;
    }

    // Flash LED at normal rate

    else
    {
      GPIOPIN61OUT = i >> 20;
    }
  }
#endif

// Flash BlueBoard LPC1768-Mini-DK2 test LEDs

#ifdef LPC1768_MINI_DK2
  gpiopin_configure(GPIOPIN121, GPIOPIN_OUTPUT);	// Test LED LD2
  gpiopin_configure(GPIOPIN122, GPIOPIN_OUTPUT);	// Test LED LD3
  gpiopin_configure(GPIOPIN75, GPIOPIN_INPUT);		// Push button KEY1

  for (i = 0;; i++)
  {
    // Flash faster if button is pressed

    if (!GPIOPIN75IN)
    {
      GPIOPIN121OUT = i >> 18;
      GPIOPIN122OUT = i >> 19;
    }

    // Flash LED at normal rate

    else
    {
      GPIOPIN121OUT = i >> 19;
      GPIOPIN122OUT = i >> 20;
    }
  }
#endif
}
