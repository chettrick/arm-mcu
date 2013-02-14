/* Abstract services for controlling LPC11xx GPIO pins */

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

#ifndef _GPIO_H
#define _GPIO_H

#include <_ansi.h>
#include <stdint.h>

_BEGIN_STD_C

typedef enum
{
  P0_0	= 0,		// P0.0
  P0_1	= 1,		// P0.1
  P0_2	= 2,		// P0.2
  P0_3	= 3,		// P0.3
  P0_4	= 4,		// P0.4
  P0_5	= 5,		// P0.5
  P0_6	= 6,		// P0.6
  P0_7	= 7,		// P0.7
  P0_8	= 8,		// P0.8
  P0_9	= 9,		// P0.9
  P0_10	= 10,		// P0.10
  P0_11	= 11,		// P0.11
  P1_0	= 12,		// P1.0
  P1_1	= 13,		// P1.1
  P1_2	= 14,		// P1.2
  P1_3	= 15,		// P1.3
  P1_4	= 16,		// P1.4
  P1_5	= 17,		// P1.5
  P1_6	= 18,		// P1.6
  P1_7	= 19,		// P1.7
  P1_8	= 20,		// P1.8
  P1_9	= 21,		// P1.9
  P1_10	= 22,		// P1.10
  P1_11	= 23,		// P1.11
  P2_0	= 24,		// P2.0
  P2_1	= 25,		// P2.1
  P2_2	= 26,		// P2.2
  P2_3	= 27,		// P2.3
  P2_4	= 28,		// P2.4
  P2_5	= 29,		// P2.5
  P2_6	= 30,		// P2.6
  P2_7	= 31,		// P2.7
  P2_8	= 32,		// P2.8
  P2_9	= 33,		// P2.9
  P2_10	= 34,		// P2.10
  P2_11	= 35,		// P2.11
  P3_0	= 36,		// P3.0
  P3_1	= 37,		// P3.1
  P3_2	= 38,		// P3.2
  P3_3	= 39,		// P3.3
  P3_4	= 40,		// P3.4
  P3_5	= 41,		// P3.5
  MAX_GPIO_PINS
} GPIO_PIN_T;

// GPIO pins can be configured for one of the following modes:

typedef enum
{
  GPIO_MODE_INPUT,	// Input with pull-up resistor
  GPIO_MODE_OUTPUT,	// Push-pull output
  GPIO_MODE_SENTINEL
} GPIO_MODE_t;

int gpio_configure(unsigned pin, unsigned direction);

_END_STD_C
#endif
