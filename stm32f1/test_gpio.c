/* Simple bit twiddler test program */

// $Id$

// Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
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

#ifdef OLIMEX_STM32_P103
  gpiopin_configure(GPIOPIN0, GPIOPIN_INPUT);
  gpiopin_configure(GPIOPIN44, GPIOPIN_OUTPUT);

  for (i = 0;; i++)
  {
    // Flash faster if WAKE-UP button is pressed

    if (GPIOPIN0IN)
    {
      GPIOPIN44OUT = i >> 18;
    }

    // Flash LED normal rate
    else
    {
      GPIOPIN44OUT = i >> 19;
    }
  }
#endif

#ifdef OLIMEX_STM32_P107
  gpiopin_configure(GPIOPIN0, GPIOPIN_INPUT);
  gpiopin_configure(GPIOPIN38, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN39, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN45, GPIOPIN_INPUT);

  for (i = 0;; i++)
  {
    // Flash flaster if WAKE-UP button is pressed

    if (GPIOPIN0IN)
    {
      GPIOPIN38OUT = i >> 18;
      GPIOPIN39OUT = i >> 19;
    }

    // Turn off LED's if TAMPER button is pressed

    else if (!GPIOPIN45IN)
    {
      GPIOPIN38OUT = 0;
      GPIOPIN39OUT = 0;
    }

    // Flash normal rate

    else
    {
      GPIOPIN38OUT = i >> 19;
      GPIOPIN39OUT = i >> 20;
    }
  }
#endif

#ifdef STM32_VALUE_LINE_DISCOVERY
  gpiopin_configure(GPIOPIN0, GPIOPIN_INPUT);
  gpiopin_configure(GPIOPIN40, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN41, GPIOPIN_OUTPUT);

  for (i = 0;; i++)
  {
    // Flash faster if the user button is pressed
    if (GPIOPIN0IN)
    {
      GPIOPIN40OUT = i >> 17;
      GPIOPIN41OUT = i >> 18;
    }

    // Flash normal rate
    else
    {
      GPIOPIN40OUT = i >> 18;
      GPIOPIN41OUT = i >> 19;
    }
  }
#endif

#ifdef W5200E01_M3
  gpiopin_configure(GPIOPIN0, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN1, GPIOPIN_OUTPUT);

  for (i = 0;; i++)
  {
    GPIOPIN0OUT = i >> 19;
    GPIOPIN1OUT = i >> 20;
  }
#endif
}
