/* Abstract services for controlling LPC11xx GPIO pins */

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

#ifndef _GPIO_H
#define _GPIO_H

_BEGIN_STD_C

// These are all the LPC11xx GPIO pins -- Not all are bonded out

typedef enum
{
  PIO0_0	= 0,
  PIO0_1	= 1,
  PIO0_2	= 2,
  PIO0_3	= 3,
  PIO0_4	= 4,
  PIO0_5	= 5,
  PIO0_6	= 6,
  PIO0_7	= 7,
  PIO0_8	= 8,
  PIO0_9	= 9,
  PIO0_10	= 10,
  PIO0_11	= 11,
  PIO1_0	= 12,
  PIO1_1	= 13,
  PIO1_2	= 14,
  PIO1_3	= 15,
  PIO1_4	= 16,
  PIO1_5	= 17,
  PIO1_6	= 18,
  PIO1_7	= 19,
  PIO1_8	= 20,
  PIO1_9	= 21,
  PIO1_10	= 22,
  PIO1_11	= 23,
  PIO2_0	= 24,
  PIO2_1	= 25,
  PIO2_2	= 26,
  PIO2_3	= 27,
  PIO2_4	= 28,
  PIO2_5	= 29,
  PIO2_6	= 30,
  PIO2_7	= 31,
  PIO2_8	= 32,
  PIO2_9	= 33,
  PIO2_10	= 34,
  PIO2_11	= 35,
  PIO3_0	= 36,
  PIO3_1	= 37,
  PIO3_2	= 38,
  PIO3_3	= 39,
  PIO3_4	= 40,
  PIO3_5	= 41,
  MAX_GPIO_PINS
} GPIO_PIN_T;

// GPIO pins can be configured for one of the following modes:

typedef enum
{
  GPIO_MODE_INPUT,		// High impedance input
  GPIO_MODE_INPUT_PULLDOWN,
  GPIO_MODE_INPUT_PULLUP,
  GPIO_MODE_OUTPUT,		// Push-pull output
  GPIO_MODE_OUTPUT_OPENDRAIN,
  MAX_GPIO_MODES
} GPIO_MODE_t;

// GPIO input pins can be configured for one of the following interrupt modes:

typedef enum
{
  GPIO_INTERRUPT_DISABLED,
  GPIO_INTERRUPT_FALLING,
  GPIO_INTERRUPT_RISING,
  GPIO_INTERRUPT_BOTH,
  GPIO_INTERRUPT_LOW,
  GPIO_INTERRUPT_HIGH,
  MAX_GPIO_INTERRUPT_CONFIGS
} GPIO_INTERRUPT_CONFIG_t;

// GPIO service functions

int gpio_configure(unsigned pin, GPIO_MODE_t mode);
int gpio_configure_interrupt(unsigned pin, GPIO_INTERRUPT_CONFIG_t config);
int gpio_configure_function(unsigned pin, unsigned function);
int gpio_read(unsigned pin);
int gpio_write(unsigned pin, bool state);

_END_STD_C
#endif
