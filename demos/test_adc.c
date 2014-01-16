/* Simple A/D Converter Test program */

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cpu.h>

#define SYSTICKRATE     100

_BEGIN_STD_C

static volatile int TimerCounter = 0;
static volatile int TimerFlag = false;

void SysTick_Handler(void)
{
  if (++TimerCounter == SYSTICKRATE/5)
  {
    TimerCounter = 0;
    TimerFlag = true;
  }
}

_END_STD_C

#define MAX_CHANNELS	8

int main(void)
{
  int channel;
  uint16_t results[MAX_CHANNELS];

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef CONSOLE_SERIAL
  serial_stdio(CONSOLE_PORT);
#endif

#ifdef CONSOLE_SEMIHOSTING
  semihosting_stdio(CONSOLE_PORT)
#endif

#ifdef CONSOLE_USB
  usb_serial_stdio(NULL);
  getch();
#endif

  printf("\033[H\033[2J%s A/D Converter Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  puts(revision);
  printf("\nCPU Freq:%u Hz  Compiler:%s %s %s\n\n", (unsigned int) SystemCoreClock,
    __COMPILER__, __VERSION__, __ABI__);

// Initialize A/D inputs

  for (channel = 0; channel <= 7; channel++)
    if (adc_init(channel) < 0)
      printf("ERROR: adc_init() for channel %d failed, %s\n", channel, strerror(errno));

  putchar('\n');

// Initialize System Tick

  SysTick_Config(SystemCoreClock / SYSTICKRATE);

  for (;;)
  {
    if (TimerFlag)
    {
      for (channel = 0; channel < MAX_CHANNELS; channel++)
        results[channel] = adc_read(channel);

      for (channel = 0; channel < MAX_CHANNELS; channel++)
        printf("%05d ", results[channel]);

      putchar('\r');

      TimerFlag = false;
    }
  }
}
