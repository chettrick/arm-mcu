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

static const char revision[] = "$Id$";

#include <cpu.h>

// The following table calculates (at compile time) as much as possible
// the addresses and data values necessary to manipulate GPIO pins.
// We trade 840 bytes of flash for a major boost in run-time performance.

static const struct
{
  volatile uint32_t *iocon;
  volatile uint32_t *ddr;
  volatile uint32_t *data;
  uint16_t modes[GPIO_MODE_SENTINEL];
  uint16_t ddrbit[GPIO_MODE_SENTINEL];
} gpio_pin_table[MAX_GPIO_PINS] =
{
  { &LPC_IOCON->RESET_PIO0_0,	&LPC_GPIO0->DIR, &LPC_GPIO0->MASKED_ACCESS[0x001], { 0xF1, 0xC1 }, { 0xFFE, 0x001 } },
  { &LPC_IOCON->PIO0_1,		&LPC_GPIO0->DIR, &LPC_GPIO0->MASKED_ACCESS[0x002], { 0xF0, 0xC0 }, { 0xFFD, 0x002 } },
  { &LPC_IOCON->PIO0_2,		&LPC_GPIO0->DIR, &LPC_GPIO0->MASKED_ACCESS[0x004], { 0xF0, 0xC0 }, { 0xFFB, 0x004 } },
  { &LPC_IOCON->PIO0_3,		&LPC_GPIO0->DIR, &LPC_GPIO0->MASKED_ACCESS[0x008], { 0xF0, 0xC0 }, { 0xFF7, 0x008 } },
  { &LPC_IOCON->PIO0_4,		&LPC_GPIO0->DIR, &LPC_GPIO0->MASKED_ACCESS[0x010], { 0x100, 0x100 }, { 0xFEF, 0x010 } },
  { &LPC_IOCON->PIO0_5,		&LPC_GPIO0->DIR, &LPC_GPIO0->MASKED_ACCESS[0x020], { 0x100, 0x100 }, { 0xFDF, 0x020 } },
  { &LPC_IOCON->PIO0_6,		&LPC_GPIO0->DIR, &LPC_GPIO0->MASKED_ACCESS[0x040], { 0xF0, 0xC0 }, { 0xFBF, 0x040 } },
  { &LPC_IOCON->PIO0_7,		&LPC_GPIO0->DIR, &LPC_GPIO0->MASKED_ACCESS[0x080], { 0xF0, 0xC0 }, { 0xF7F, 0x080 } },
  { &LPC_IOCON->PIO0_8,		&LPC_GPIO0->DIR, &LPC_GPIO0->MASKED_ACCESS[0x100], { 0xF0, 0xC0 }, { 0xEFF, 0x100 } },
  { &LPC_IOCON->PIO0_9,		&LPC_GPIO0->DIR, &LPC_GPIO0->MASKED_ACCESS[0x200], { 0xF0, 0xC0 }, { 0xDFF, 0x200 } },
  { &LPC_IOCON->SWCLK_PIO0_10,	&LPC_GPIO0->DIR, &LPC_GPIO0->MASKED_ACCESS[0x400], { 0xF1, 0xC1 }, { 0xBFF, 0x400 } },
  { &LPC_IOCON->R_PIO0_11,	&LPC_GPIO0->DIR, &LPC_GPIO0->MASKED_ACCESS[0x800], { 0xF1, 0xC1 }, { 0x7FF, 0x800 } },
  { &LPC_IOCON->R_PIO1_0,	&LPC_GPIO1->DIR, &LPC_GPIO1->MASKED_ACCESS[0x001], { 0xF1, 0xC1 }, { 0xFFE, 0x001 } },
  { &LPC_IOCON->R_PIO1_1,	&LPC_GPIO1->DIR, &LPC_GPIO1->MASKED_ACCESS[0x002], { 0xF1, 0xC1 }, { 0xFFD, 0x002 } },
  { &LPC_IOCON->R_PIO1_2,	&LPC_GPIO1->DIR, &LPC_GPIO1->MASKED_ACCESS[0x004], { 0xF1, 0xC1 }, { 0xFFB, 0x004 } },
  { &LPC_IOCON->SWDIO_PIO1_3,	&LPC_GPIO1->DIR, &LPC_GPIO1->MASKED_ACCESS[0x008], { 0xF1, 0xC1 }, { 0xFF7, 0x008 } },
  { &LPC_IOCON->PIO1_4,		&LPC_GPIO1->DIR, &LPC_GPIO1->MASKED_ACCESS[0x010], { 0xF0, 0xC0 }, { 0xFEF, 0x010 } },
  { &LPC_IOCON->PIO1_5,		&LPC_GPIO1->DIR, &LPC_GPIO1->MASKED_ACCESS[0x020], { 0xF0, 0xC0 }, { 0xFDF, 0x020 } },
  { &LPC_IOCON->PIO1_6,		&LPC_GPIO1->DIR, &LPC_GPIO1->MASKED_ACCESS[0x040], { 0xF0, 0xC0 }, { 0xFBF, 0x040 } },
  { &LPC_IOCON->PIO1_7,		&LPC_GPIO1->DIR, &LPC_GPIO1->MASKED_ACCESS[0x080], { 0xF0, 0xC0 }, { 0xF7F, 0x080 } },
  { &LPC_IOCON->PIO1_8,		&LPC_GPIO1->DIR, &LPC_GPIO1->MASKED_ACCESS[0x100], { 0xF0, 0xC0 }, { 0xEFF, 0x100 } },
  { &LPC_IOCON->PIO1_9,		&LPC_GPIO1->DIR, &LPC_GPIO1->MASKED_ACCESS[0x200], { 0xF0, 0xC0 }, { 0xDFF, 0x200 } },
  { &LPC_IOCON->PIO1_10,	&LPC_GPIO1->DIR, &LPC_GPIO1->MASKED_ACCESS[0x400], { 0xF0, 0xC0 }, { 0xBFF, 0x400 } },
  { &LPC_IOCON->PIO1_11,	&LPC_GPIO1->DIR, &LPC_GPIO1->MASKED_ACCESS[0x800], { 0xF0, 0xC0 }, { 0x7FF, 0x800 } },
  { &LPC_IOCON->PIO2_0,		&LPC_GPIO2->DIR, &LPC_GPIO2->MASKED_ACCESS[0x001], { 0xF0, 0xC0 }, { 0xFFE, 0x001 } },
  { &LPC_IOCON->PIO2_1,		&LPC_GPIO2->DIR, &LPC_GPIO2->MASKED_ACCESS[0x002], { 0xF0, 0xC0 }, { 0xFFD, 0x002 } },
  { &LPC_IOCON->PIO2_2,		&LPC_GPIO2->DIR, &LPC_GPIO2->MASKED_ACCESS[0x004], { 0xF0, 0xC0 }, { 0xFFB, 0x004 } },
  { &LPC_IOCON->PIO2_3,		&LPC_GPIO2->DIR, &LPC_GPIO2->MASKED_ACCESS[0x008], { 0xF0, 0xC0 }, { 0xFF7, 0x008 } },
  { &LPC_IOCON->PIO2_4,		&LPC_GPIO2->DIR, &LPC_GPIO2->MASKED_ACCESS[0x010], { 0xF0, 0xC0 }, { 0xFEF, 0x010 } },
  { &LPC_IOCON->PIO2_5,		&LPC_GPIO2->DIR, &LPC_GPIO2->MASKED_ACCESS[0x020], { 0xF0, 0xC0 }, { 0xFDF, 0x020 } },
  { &LPC_IOCON->PIO2_6,		&LPC_GPIO2->DIR, &LPC_GPIO2->MASKED_ACCESS[0x040], { 0xF0, 0xC0 }, { 0xFBF, 0x040 } },
  { &LPC_IOCON->PIO2_7,		&LPC_GPIO2->DIR, &LPC_GPIO2->MASKED_ACCESS[0x080], { 0xF0, 0xC0 }, { 0xF7F, 0x080 } },
  { &LPC_IOCON->PIO2_8,		&LPC_GPIO2->DIR, &LPC_GPIO2->MASKED_ACCESS[0x100], { 0xF0, 0xC0 }, { 0xEFF, 0x100 } },
  { &LPC_IOCON->PIO2_9,		&LPC_GPIO2->DIR, &LPC_GPIO2->MASKED_ACCESS[0x200], { 0xF0, 0xC0 }, { 0xDFF, 0x200 } },
  { &LPC_IOCON->PIO2_10,	&LPC_GPIO2->DIR, &LPC_GPIO2->MASKED_ACCESS[0x400], { 0xF0, 0xC0 }, { 0xBFF, 0x400 } },
  { &LPC_IOCON->PIO2_11,	&LPC_GPIO2->DIR, &LPC_GPIO2->MASKED_ACCESS[0x800], { 0xF0, 0xC0 }, { 0x7FF, 0x800 } },
  { &LPC_IOCON->PIO3_0,		&LPC_GPIO3->DIR, &LPC_GPIO3->MASKED_ACCESS[0x001], { 0xF0, 0xC0 }, { 0xFFE, 0x001 } },
  { &LPC_IOCON->PIO3_1,		&LPC_GPIO3->DIR, &LPC_GPIO3->MASKED_ACCESS[0x002], { 0xF0, 0xC0 }, { 0xFFD, 0x002 } },
  { &LPC_IOCON->PIO3_2,		&LPC_GPIO3->DIR, &LPC_GPIO3->MASKED_ACCESS[0x004], { 0xF0, 0xC0 }, { 0xFFB, 0x004 } },
  { &LPC_IOCON->PIO3_3,		&LPC_GPIO3->DIR, &LPC_GPIO3->MASKED_ACCESS[0x008], { 0xF0, 0xC0 }, { 0xFF7, 0x008 } },
  { &LPC_IOCON->PIO3_4,		&LPC_GPIO3->DIR, &LPC_GPIO3->MASKED_ACCESS[0x010], { 0xF0, 0xC0 }, { 0xFEF, 0x010 } },
  { &LPC_IOCON->PIO3_5,		&LPC_GPIO3->DIR, &LPC_GPIO3->MASKED_ACCESS[0x020], { 0xF0, 0xC0 }, { 0xFDF, 0x020 } }
};

/* Configure a single GPIO pin */

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

  if ((mode >= GPIO_MODE_OUTPUT) && (mode <= GPIO_MODE_OUTPUT))
    *gpio_pin_table[pin].ddr |= gpio_pin_table[pin].ddrbit[mode];
  else
    *gpio_pin_table[pin].ddr &= gpio_pin_table[pin].ddrbit[mode];

  return 0;
}

/* Read from a single GPIO pin */

int gpio_read(unsigned pin)
{
  errno_r = 0;

  if (pin >= MAX_GPIO_PINS)
  {
    errno_r = ENODEV;
    return -ENODEV;
  }

  if (*gpio_pin_table[pin].data)
    return 1;
  else
    return 0;
}

/* Write to a single GPIO pin */

int gpio_write(unsigned pin, unsigned value)
{
  errno_r = 0;

  if (pin >= MAX_GPIO_PINS)
  {
    errno_r = ENODEV;
    return -ENODEV;
  }

  if (value)
    *gpio_pin_table[pin].data = 0xFFF;
  else
    *gpio_pin_table[pin].data = 0x000;

  return 0;
}
