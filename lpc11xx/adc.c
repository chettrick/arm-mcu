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

#define MAX_ADC_CHANNELS	8

#define ADC_START		0x01000000
#define ADC_CLKDIV		(10 << 8)	// 48 MHz/11 = 4.36 MHz
#define ADC_DONE		0x80000000
#define ADC_ADINT		0x00010000

// Initialize an A/D input pin
//   Returns 0 on success or nonzero on failure and sets errno

int adc_init(unsigned int channel)
{
  errno_r = 0;

// Validate parameters

#if defined(RASPBERRYPI_LPC1114)
  if ((channel < 1) || (channel > 5))	// Only channels 1 to 5 are available
#elif defined(LPC1114FN28)
  if (channel > 5)			// Channels 6 and 7 are not pinned out
#else
  if (channel >= MAX_ADC_CHANNELS)
#endif
  {
    errno_r = ENODEV;
    return -ENODEV;
  }

// Power up A/D converter

  LPC_SYSCON->PDRUNCFG &= ~(1 << 4);

// Enable A/D converter peripheral clock

  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 13);

// Configure analog input pin

  switch (channel)
  {
    case 0 :
      LPC_IOCON->R_PIO0_11 = 0x00000002;	// AD0
      break;

    case 1 :
      LPC_IOCON->R_PIO1_0 = 0x00000002;		// AD1
      break;

    case 2 :
      LPC_IOCON->R_PIO1_1 = 0x00000002;		// AD2
      break;

    case 3 :
      LPC_IOCON->R_PIO1_2 = 0x00000002;		// AD3
      break;

    case 4 :
      LPC_IOCON->SWDIO_PIO1_3 = 0x00000002;	// AD4
      break;

    case 5 :
      LPC_IOCON->PIO1_4 = 0x00000001;		// AD5
      break;

    case 6 :
      LPC_IOCON->PIO1_10 = 0x00000001;		// AD6
      break;

    case 7 :
      LPC_IOCON->PIO1_11 = 0x00000001;		// AD7
      break;
  }

  return 0;
}

// Read an A/D input
//   Returns unsigned 16-bit result, right-justified, or zero on error

uint16_t adc_read(unsigned int channel)
{
  errno_r = 0;

// Validate parameters

#if defined(RASPBERRYPI_LPC1114)
  if ((channel < 1) || (channel > 5))	// Only channels 1 to 5 are available
#elif defined(LPC1114FN28)
  if (channel > 5)			// Channels 6 and 7 are not pinned out
#else
  if (channel >= MAX_ADC_CHANNELS)
#endif
  {
    errno_r = ENODEV;
    return 0;
  }

// Start conversion

  LPC_ADC->CR = ADC_START | ADC_CLKDIV | (1 << channel);

// Wait for conversion to complete

  while (!(LPC_ADC->STAT & ADC_ADINT));

// Retrieve result

  return (LPC_ADC->GDR & 0x0000FFFF) >> 6;
}
