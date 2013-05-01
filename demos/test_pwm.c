/* PWM output test program */

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef CONSOLE_CONIO
#include <conio.h>
#endif

int main(void)
{
  char buf[256];
  uint32_t channel, frequency, value;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef CONSOLE_USB
  usb_serial_stdio(NULL);
  getch();
#else
  serial_stdio(CONSOLE_PORT);
#endif

  printf("\033[H\033[2J%s PWM Output Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  puts(revision);
  printf("\nCPU Freq:%u Hz  Compiler:%s %s %s\n\n", (unsigned int) SystemCoreClock,
    __COMPILER__, __VERSION__, __ABI__);

  printf("Enter PWM channel:   ");
  gets(buf);
  channel = atoi(buf);

  printf("Enter PWM frequency: ");
  gets(buf);
  frequency = atoi(buf);

  if (pwm_init(channel, frequency))
  {
    printf("ERROR: pwm_init() failed, %s\n", strerror(errno));
    return 1;
  }

  for (;;)
  {
    printf("Enter value:         ");
    gets(buf);
    value = atoi(buf);

    if (pwm_set(channel, value))
    {
      printf("ERROR: pwm_init() failed, %s\n", strerror(errno));
      return 1;
    }
  }
}
