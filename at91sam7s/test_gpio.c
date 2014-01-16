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
  volatile unsigned int i;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef OLIMEX_SAM7_P256
#define LED1PIN		18
#define LED2PIN		17
#define LED1MASK	(1 << LED1PIN)
#define LED2MASK	(1 << LED2PIN)
#define BUTTON1PIN	19
#define BUTTON2PIN	20
#define BUTTON1MASK	(1 << BUTTON1PIN)
#define BUTTON2MASK	(1 << BUTTON2PIN)
#define BUTTON1PRESSED	(!(*AT91C_PIOA_PDSR & BUTTON1MASK))
#define BUTTON2PRESSED	(!(*AT91C_PIOA_PDSR & BUTTON2MASK))

  *AT91C_PMC_PCER	= 0x00000004;	// Enable Port A peripheral clock
  *AT91C_PIOA_PER	= LED1MASK;	// LED1 pin is GPIO
  *AT91C_PIOA_PPUDR	= LED1MASK;	// LED1 pin does not need internal pullup
  *AT91C_PIOA_OER	= LED1MASK;	// LED1 pin is output
  *AT91C_PIOA_OWER	= LED1MASK;	// LED1 pin is synchronous output
  *AT91C_PIOA_MDER	= LED1MASK;	// LED1 pin is open drain output

  *AT91C_PIOA_PER	= LED2MASK;	// LED2 pin is GPIO
  *AT91C_PIOA_PPUDR	= LED2MASK;	// LED2 pin does not need internal pullup
  *AT91C_PIOA_OER	= LED2MASK;	// LED2 pin is output
  *AT91C_PIOA_OWER	= LED2MASK;	// LED2 pin is synchronous output
  *AT91C_PIOA_MDER	= LED2MASK;	// LED2 pin is open drain output

  *AT91C_PIOA_PER	= BUTTON1MASK;	// BUTTON1 pin is GPIO
  *AT91C_PIOA_PPUDR	= BUTTON1MASK;	// BUTTON1 pin does not need internal pullup
  *AT91C_PIOA_ODR	= BUTTON1MASK;	// BUTTON1 pin is input
  *AT91C_PIOA_IFER	= BUTTON1MASK;	// BUTTON1 pin is filtered

  *AT91C_PIOA_PER	= BUTTON2MASK;	// BUTTON2 pin is GPIO
  *AT91C_PIOA_PPUDR	= BUTTON2MASK;	// BUTTON2 pin does not need internal pullup
  *AT91C_PIOA_ODR	= BUTTON2MASK;	// BUTTON2 pin is input
  *AT91C_PIOA_IFER	= BUTTON2MASK;	// BUTTON2 pin is filtered

  for (i = 0;; i++)
  {
    // Flash LED's faster if user button 1 is pressed

    if (BUTTON1PRESSED)
    {
      *AT91C_PIOA_ODSR = i >> 1;	// Flash LED's faster
    }

    // Turn off LED's if user button 2 is pressed

    else if (BUTTON2PRESSED)
    {
      *AT91C_PIOA_ODSR = 0xFFFFFFFF;	// Turn off LED's
    }

    // Flash LED's at the normal rate

    else
    {
      *AT91C_PIOA_ODSR = i >> 2;	// Flash LED's slower
    }
  }
#endif
}
