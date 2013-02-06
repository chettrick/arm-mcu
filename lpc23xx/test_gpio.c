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

#ifdef OLIMEX_LPC_P2378
#define LEDMASK		(1 << 19)
#define BUT1MASK	(1 << 30)
#define BUT2MASK	(1 << 6)
#define BUT1PRESSED	(!(FIO0PIN & BUT1MASK))
#define BUT2PRESSED	(!(FIO0PIN & BUT2MASK))

  PCLKSEL1 = 0x00000004;	// GPIO peripheral clock is CCLK/1

  FIO1MASK &= ~LEDMASK;		// Unmask LED pin
  FIO0MASK &= ~BUT1MASK;	// Unmask Button 1 pin
  FIO0MASK &= ~BUT2MASK;	// Unmask Button 2 pin

  FIO1DIR |= LEDMASK;		// Make LED pin output
  FIO0DIR &= ~BUT1MASK;		// Make Button 1 pin input
  FIO0DIR &= ~BUT1MASK;		// Make Button 2 pin input

  for (i = 0;; i++)
  {
    // Flash faster if Button 1 is pressed

    if (BUT1PRESSED)
    {
      FIO1PIN = i << 1;
    }

    // Turn off LED if Button 2 is pressed

    else if (BUT2PRESSED)
    {
      FIO1PIN = LEDMASK;
    }

    // Flash normally

    else
    {
      FIO1PIN = i;
    }
  }
#endif

#ifdef MBED_LPC2368
#define LEDMASK ((1 << 18)|(1 << 20)|(1 << 21)|(1 << 23))
  PCLKSEL1 = 0x00000004;	// GPIO peripheral clock is CCLK/1

  FIO1MASK &= ~LEDMASK;		// Unmask LED pins
  FIO1DIR |= LEDMASK;		// Make output LED pins

  for (i = 0;; i++)
    FIO1PIN = i;
#endif
}
