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
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef LPC1114FN28
  LPC_IOCON->PIO0_7 = 0xC0;			// PIO0.7 is GPIO
  LPC_GPIO0->DIR = 0x80;			// P0.7 is output
#endif

#ifdef PROTOBOARD_LPC1114FN28
  LPC_IOCON->R_PIO1_0 = 0xC1;			// Configure PIO1 pins for GPIO
  LPC_IOCON->R_PIO1_1 = 0xC1;
  LPC_IOCON->R_PIO1_2 = 0xC1;
  LPC_IOCON->PIO1_4 = 0xC0;
  LPC_IOCON->PIO1_5 = 0xC0;
  LPC_IOCON->PIO1_6 = 0xC0;
  LPC_IOCON->PIO1_7 = 0xC0;
  LPC_IOCON->PIO1_8 = 0xC0;
  LPC_IOCON->PIO1_9 = 0xC0;
  LPC_GPIO1->DIR = 0x3F7;			// P1.0-P1.9 are outputs
#endif

  for (i = 0;; i++)
  {
#ifdef LPC1114FN28
    LPC_GPIO0->DATA = i >> 11;			// Flash LED
#endif

#ifdef PROTOBOARD_LPC1114
    LPC_GPIO1->DATA = i;			// Toggle P1 GPIO's
#endif
  }
}
