/* PWM output test program */

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

int main(void)
{
  char buf[256];
  uint32_t channel, frequency, setting;

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

  printf("\033[H\033[2J%s PWM Output Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  puts(revision);
  printf("\nCPU Freq:%u Hz  Compiler:%s %s %s\n\n", (unsigned int) SystemCoreClock,
    __COMPILER__, __VERSION__, __ABI__);

  for (;;)
  {
    printf("Enter PWM channel:            ");
    gets(buf);
    channel = atoi(buf);

    printf("Enter PWM frequency:          ");
    gets(buf);
    frequency = atoi(buf);

    if (pwm_init(channel, frequency))
    {
      printf("ERROR: pwm_init() failed, %s\n", strerror(errno));
      continue;
    }

    for (;;)
    {
      printf("Enter PWM setting (0-65535):  ");
      gets(buf);
      setting = atoi(buf);

      if (setting == 0xFFFFFFFF)
      {
        putchar('\n');
        break;
      }

      if (pwm_set(channel, setting))
      {
        printf("ERROR: pwm_set() failed, %s\n", strerror(errno));
        continue;
      }
    }
  }
}
