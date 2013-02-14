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

static const char revision[] = "$Id: adc.c 4710 2013-02-06 08:47:48Z svn $";

#include <cpu.h>
#include <errno.h>

static const struct
{
  volatile uint32_t *iocon;
  uint32_t modes[GPIO_MODE_SENTINEL];
} gpio_pin_table[MAX_GPIO_PINS] =
{
  { &LPC_IOCON->RESET_PIO0_0, 		{ 0x00, 0x00 } },
  { &LPC_IOCON->PIO0_1,			{ 0x00, 0x00 } },
  { &LPC_IOCON->PIO0_2,			{ 0x00, 0x00 } },
  { &LPC_IOCON->PIO0_3,			{ 0x00, 0x00 } },
  { &LPC_IOCON->PIO0_4,			{ 0x00, 0x00 } },
  { &LPC_IOCON->PIO0_5,			{ 0x00, 0x00 } },
  { &LPC_IOCON->PIO0_6,			{ 0x00, 0x00 } },
  { &LPC_IOCON->PIO0_7,			{ 0x00, 0x00 } },
  { &LPC_IOCON->PIO0_8,			{ 0x00, 0x00 } },
  { &LPC_IOCON->PIO0_9,			{ 0x00, 0x00 } },
  { &LPC_IOCON->SWCLK_PIO0_10,		{ 0x00, 0x00 } },
  { &LPC_IOCON->R_PIO0_11,		{ 0x00, 0x00 } },
};

int gpio_configure(unsigned pin, unsigned mode)
{
  errno_r = 0;

  if (pin >= MAX_GPIO_PINS)
  {
    errno_r = ENODEV;
    return -ENODEV;
  }

  if (mode >= GPIO_MODE_SENTINEL)
  {
    errno_r = EINVAL;
    return -EINVAL;
  }

  *gpio_pin_table[pin].iocon = gpio_pin_table[pin].modes[mode];
  return 0;
}
