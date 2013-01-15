/* Simple bit twiddler test program for the STR91x ARM MCU */

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

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);

#ifdef STMICRO_STR910_EVAL
  GPIO_InitTypeDef config;
  unsigned long int i;

  SCU_APBPeriphClockConfig(__GPIO7, ENABLE);	// Turn on GPIO7 clock
  SCU_APBPeriphReset(__GPIO7, DISABLE);		// Let GPIO7 out of reset

  SCU_APBPeriphClockConfig(__GPIO9, ENABLE);	// Turn on GPIO9 clock
  SCU_APBPeriphReset(__GPIO9, DISABLE);		// Let GPIO9 out of reset

  // Initialize LED output pins
 
  GPIO_StructInit(&config);
  config.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  config.GPIO_Direction = GPIO_PinOutput;	// LED pins are outputs
  config.GPIO_Type = GPIO_Type_PushPull;	// LED pins are push pull outputs
  config.GPIO_Alternate = GPIO_OutputAlt1;	// LED pins are GPIO outputs
  GPIO_Init(GPIO9, &config);

  // Initialize joystick input pins

  GPIO_StructInit(&config);
  config.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  config.GPIO_Direction = GPIO_PinInput;	// Joystick pins are inputs
  config.GPIO_Alternate = GPIO_InputAlt1;	// Joystick pins are GPIO inputs
  config.GPIO_IPInputConnected = GPIO_IPInputConnected_Disable;
  GPIO_Init(GPIO7, &config);

  for (i = 0;; i++)
  {
    // Speed up flashing if joystick is UP

    if ((GPIO_Read(GPIO7) >> 4) == 8)
    {
      GPIO_Write(GPIO9, ~(i >> 15));
    }

    // Slow down flashing if joystick is DOWN

    else if ((GPIO_Read(GPIO7) >> 4) == 2)
    {
      GPIO_Write(GPIO9, ~(i >> 17));
    }

    // Turn off LED's if PB3 is pressed

    else if ((GPIO_Read(GPIO7) >> 4) == 10)
    {
      GPIO_Write(GPIO9, 0xFF);
    }

    // Normal flashing

    else
    {
      GPIO_Write(GPIO9, ~(i >> 16));
    }
  }
#endif
}
