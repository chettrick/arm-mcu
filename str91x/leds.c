/* Abstract services for controlling LED's */

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

#define MAX_LEDS	4

// Initialize the LED's (to the off state)

void LEDS_initialize(void)
{
#ifdef STMICRO_STR910_EVAL
  GPIO_InitTypeDef config;

  SCU_APBPeriphClockConfig(__GPIO9, ENABLE);		// Turn on GPIO9 clock
  SCU_APBPeriphReset(__GPIO9, DISABLE);			// Let GPIO9 out of reset

  GPIO_StructInit(&config);
  config.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  config.GPIO_Direction = GPIO_PinOutput;		// LED pins are outputs
  config.GPIO_Type = GPIO_Type_PushPull;		// LED pins are push pull outputs
  config.GPIO_Alternate = GPIO_OutputAlt1;		// LED pins are GPIO outputs
  GPIO_Init(GPIO9, &config);
#endif

  LEDS_set(0);						// Turn off all LEDs at startup
}

// Get LED states.  A 1 bit in the result indicates the LED is on.
// A 0 bit in the result indicates the LED is off.

unsigned long int LEDS_get(void)
{
  unsigned long int result = 0;

#ifdef STMICRO_STR910_EVAL
  result = (~GPIO_Read(GPIO9)) & 0x0F;
#endif

  return result;
}

// Set LED states.  A 1 bit in the mask indicates the LED should be turned on.
// A 0 bit in the mask indicates the LED should be turned off.

void LEDS_set(unsigned long int mask)
{
#ifdef STMICRO_STR910_EVAL
  int i;

  for (i = 0; i < MAX_LEDS; i++)
  {
    if (mask & 0x01)
    {
      GPIO_WriteBit(GPIO9, (1 << i), Bit_RESET);
    }
    else
    {
      GPIO_WriteBit(GPIO9, (1 << i), Bit_SET);
    }

    mask >>= 1;
  }
#endif
}
