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

static const char revision[] = "$Id$";

#include <cpu.h>

// The following table calculates (at compile time) as much as possible
// the addresses and data values necessary to manipulate GPIO pins.
// We trade 1008 bytes of flash for a major boost in run-time performance.

static const struct
{
  LPC_GPIO_TypeDef *port;
  volatile uint32_t *iocon;
  volatile uint32_t *data;
  uint16_t modes[MAX_GPIO_MODES];
} gpio_pin_table[MAX_GPIO_PINS] =
{
  { LPC_GPIO0, &LPC_IOCON->RESET_PIO0_0,  &LPC_GPIO0->MASKED_ACCESS[0x0001], { 0x0E1, 0x0E9, 0x0F1, 0x0C1, 0x4C1 }},
  { LPC_GPIO0, &LPC_IOCON->PIO0_1,        &LPC_GPIO0->MASKED_ACCESS[0x0002], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO0, &LPC_IOCON->PIO0_2,        &LPC_GPIO0->MASKED_ACCESS[0x0004], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO0, &LPC_IOCON->PIO0_3,        &LPC_GPIO0->MASKED_ACCESS[0x0008], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO0, &LPC_IOCON->PIO0_4,        &LPC_GPIO0->MASKED_ACCESS[0x0010], { 0x100, 0x100, 0x100, 0x100, 0x100 }},
  { LPC_GPIO0, &LPC_IOCON->PIO0_5,        &LPC_GPIO0->MASKED_ACCESS[0x0020], { 0x100, 0x100, 0x100, 0x100, 0x100 }},
  { LPC_GPIO0, &LPC_IOCON->PIO0_6,        &LPC_GPIO0->MASKED_ACCESS[0x0040], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO0, &LPC_IOCON->PIO0_7,        &LPC_GPIO0->MASKED_ACCESS[0x0080], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO0, &LPC_IOCON->PIO0_8,        &LPC_GPIO0->MASKED_ACCESS[0x0100], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO0, &LPC_IOCON->PIO0_9,        &LPC_GPIO0->MASKED_ACCESS[0x0200], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO0, &LPC_IOCON->SWCLK_PIO0_10, &LPC_GPIO0->MASKED_ACCESS[0x0400], { 0x0E1, 0x0E9, 0x0F1, 0x0C1, 0x4C1 }},
  { LPC_GPIO0, &LPC_IOCON->R_PIO0_11,     &LPC_GPIO0->MASKED_ACCESS[0x0800], { 0x0E1, 0x0E9, 0x0F1, 0x0C1, 0x4C1 }},
  { LPC_GPIO1, &LPC_IOCON->R_PIO1_0,      &LPC_GPIO1->MASKED_ACCESS[0x0001], { 0x0E1, 0x0E9, 0x0F1, 0x0C1, 0x4C1 }},
  { LPC_GPIO1, &LPC_IOCON->R_PIO1_1,      &LPC_GPIO1->MASKED_ACCESS[0x0002], { 0x0E1, 0x0E9, 0x0F1, 0x0C1, 0x4C1 }},
  { LPC_GPIO1, &LPC_IOCON->R_PIO1_2,      &LPC_GPIO1->MASKED_ACCESS[0x0004], { 0x0E1, 0x0E9, 0x0F1, 0x0C1, 0x4C1 }},
  { LPC_GPIO1, &LPC_IOCON->SWDIO_PIO1_3,  &LPC_GPIO1->MASKED_ACCESS[0x0008], { 0x0E1, 0x0E9, 0x0F1, 0x0C1, 0x4C1 }},
  { LPC_GPIO1, &LPC_IOCON->PIO1_4,        &LPC_GPIO1->MASKED_ACCESS[0x0010], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO1, &LPC_IOCON->PIO1_5,        &LPC_GPIO1->MASKED_ACCESS[0x0020], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO1, &LPC_IOCON->PIO1_6,        &LPC_GPIO1->MASKED_ACCESS[0x0040], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO1, &LPC_IOCON->PIO1_7,        &LPC_GPIO1->MASKED_ACCESS[0x0080], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO1, &LPC_IOCON->PIO1_8,        &LPC_GPIO1->MASKED_ACCESS[0x0100], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO1, &LPC_IOCON->PIO1_9,        &LPC_GPIO1->MASKED_ACCESS[0x0200], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO1, &LPC_IOCON->PIO1_10,       &LPC_GPIO1->MASKED_ACCESS[0x0400], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO1, &LPC_IOCON->PIO1_11,       &LPC_GPIO1->MASKED_ACCESS[0x0800], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO2, &LPC_IOCON->PIO2_0,        &LPC_GPIO2->MASKED_ACCESS[0x0001], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO2, &LPC_IOCON->PIO2_1,        &LPC_GPIO2->MASKED_ACCESS[0x0002], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO2, &LPC_IOCON->PIO2_2,        &LPC_GPIO2->MASKED_ACCESS[0x0004], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO2, &LPC_IOCON->PIO2_3,        &LPC_GPIO2->MASKED_ACCESS[0x0008], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO2, &LPC_IOCON->PIO2_4,        &LPC_GPIO2->MASKED_ACCESS[0x0010], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO2, &LPC_IOCON->PIO2_5,        &LPC_GPIO2->MASKED_ACCESS[0x0020], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO2, &LPC_IOCON->PIO2_6,        &LPC_GPIO2->MASKED_ACCESS[0x0040], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO2, &LPC_IOCON->PIO2_7,        &LPC_GPIO2->MASKED_ACCESS[0x0080], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO2, &LPC_IOCON->PIO2_8,        &LPC_GPIO2->MASKED_ACCESS[0x0100], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO2, &LPC_IOCON->PIO2_9,        &LPC_GPIO2->MASKED_ACCESS[0x0200], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO2, &LPC_IOCON->PIO2_10,       &LPC_GPIO2->MASKED_ACCESS[0x0400], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO2, &LPC_IOCON->PIO2_11,       &LPC_GPIO2->MASKED_ACCESS[0x0800], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO3, &LPC_IOCON->PIO3_0,        &LPC_GPIO3->MASKED_ACCESS[0x0001], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO3, &LPC_IOCON->PIO3_1,        &LPC_GPIO3->MASKED_ACCESS[0x0002], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO3, &LPC_IOCON->PIO3_2,        &LPC_GPIO3->MASKED_ACCESS[0x0004], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO3, &LPC_IOCON->PIO3_3,        &LPC_GPIO3->MASKED_ACCESS[0x0008], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO3, &LPC_IOCON->PIO3_4,        &LPC_GPIO3->MASKED_ACCESS[0x0010], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
  { LPC_GPIO3, &LPC_IOCON->PIO3_5,        &LPC_GPIO3->MASKED_ACCESS[0x0020], { 0x0E0, 0x0E8, 0x0F0, 0x0C0, 0x4C0 }},
};

/* Configure a single GPIO pin */

int gpio_configure(unsigned pin, GPIO_MODE_t mode)
{
  errno_r = 0;

  // Validate parameters

  if (pin >= MAX_GPIO_PINS)
  {
    errno_r = ENODEV;
    return -ENODEV;
  }

  if (mode >= MAX_GPIO_MODES)
  {
    errno_r = EINVAL;
    return -EINVAL;
  }

  // Disable interrupts

  gpio_configure_interrupt(pin, GPIO_INTERRUPT_DISABLED);

  // Configure the GPIO pin

  *gpio_pin_table[pin].iocon = gpio_pin_table[pin].modes[mode];

  // Configure the GPIO pin direction

  switch (mode)
  {
    case GPIO_MODE_INPUT :
    case GPIO_MODE_INPUT_PULLDOWN :
    case GPIO_MODE_INPUT_PULLUP :
      gpio_pin_table[pin].port->DIR &= ~(1 << (pin % 12));
      break;

    case GPIO_MODE_OUTPUT :
    case GPIO_MODE_OUTPUT_OPENDRAIN :
      gpio_pin_table[pin].port->DIR |= (1 << (pin % 12));
      break;

    default :
      errno_r = EINVAL;
      return -EINVAL;
  };

  return 0;
}

/* Configure the interrupt mode for a single GPIO pin */

int gpio_configure_interrupt(unsigned pin, GPIO_INTERRUPT_CONFIG_t config)
{
  errno_r = 0;

  // Validate parameters

  if (pin >= MAX_GPIO_PINS)
  {
    errno_r = ENODEV;
    return -ENODEV;
  }

  if (config >= MAX_GPIO_INTERRUPT_CONFIGS)
  {
    errno_r = EINVAL;
    return -EINVAL;
  }

  LPC_GPIO_TypeDef *port = gpio_pin_table[pin].port;

  unsigned mask = (1 << (pin % 12));

  switch (config)
  {
    case GPIO_INTERRUPT_DISABLED :
      port->IS  &= ~mask;	// Edge
      port->IBE &= ~mask;	// Only one edge
      port->IEV &= ~mask;	// Falling / active low
      port->IE  &= ~mask;	// Masked
      break;

    case GPIO_INTERRUPT_FALLING :
      port->IS  &= ~mask;	// Edge
      port->IBE &= ~mask;	// Only one edge
      port->IEV &= ~mask;	// Falling edge
      port->IE  |= mask;	// Enabled
      break;

    case GPIO_INTERRUPT_RISING :
      port->IS  &= ~mask;	// Edge
      port->IBE &= ~mask;	// Only one edge
      port->IEV |= mask;	// Rising edge
      port->IE  |= mask;	// Enabled
      break;

    case GPIO_INTERRUPT_BOTH :
      port->IS  &= ~mask;	// Edge
      port->IBE |= mask;	// Both edges
      port->IEV &= ~mask;
      port->IE  |= mask;	// Enabled
      break;

    case GPIO_INTERRUPT_LOW :
      port->IS  |= mask;	// Level
      port->IBE &= ~mask;
      port->IEV &= ~mask;	// Active low
      port->IE  |= mask;	// Enabled
      break;

    case GPIO_INTERRUPT_HIGH :
      port->IS  |= mask;	// Level
      port->IBE &= ~mask;
      port->IEV |= mask;	// Active high
      port->IE  |= mask;	// Enabled
      break;

    default :
      errno_r = EINVAL;
      return -EINVAL;
  }

  return 0;
}

/* Configure a GPIO pin function (call after gpio_configure()) */

int gpio_configure_function(unsigned pin, unsigned function)
{
  errno_r = 0;

  // Validate parameters

  if (pin >= MAX_GPIO_PINS)
  {
    errno_r = ENODEV;
    return -ENODEV;
  }

  if (function > 7)
  {
    errno_r = EINVAL;
    return -EINVAL;
  }

  *gpio_pin_table[pin].iocon &= 0xFFFFFFF8;
  *gpio_pin_table[pin].iocon |= function;
  return 0;
}

/* Read from a single GPIO pin */

int gpio_read(unsigned pin)
{
  errno_r = 0;

  // Validate parameters

  if (pin >= MAX_GPIO_PINS)
  {
    errno_r = ENODEV;
    return -ENODEV;
  }

  // Read the pin

  if (*gpio_pin_table[pin].data)
    return 1;
  else
    return 0;
}

/* Write to a single GPIO pin */

int gpio_write(unsigned pin, bool value)
{
  errno_r = 0;

  // Validate parameters

  if (pin >= MAX_GPIO_PINS)
  {
    errno_r = ENODEV;
    return -ENODEV;
  }

  // Write the pin

  if (value)
    *gpio_pin_table[pin].data = 0xFFF;
  else
    *gpio_pin_table[pin].data = 0x000;

  return 0;
}
