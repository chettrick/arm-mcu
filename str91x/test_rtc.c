/* Simple real time clock test program for the STR91x ARM MCU */

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

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <cpu.h>

int main(void)
{
  RTC_TIME t_rtc;
  RTC_DATE d_rtc;
  char buf[256];
  int year, month, day, hour, minute, second;
  time_t then, now;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef CONSOLE_USB
  usb_serial_stdio(NULL);
  getch();
#else
  serial_stdio(CONSOLE_PORT);
#endif

  puts("\033[H\033[2JSTR91x Real Time Clock Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%u Hz  Compiler:%s %s %s\n\n", (unsigned int) SystemCoreClock,
    __COMPILER__, __VERSION__, __ABI__);

// Turn on RTC peripheral clock

  SCU_APBPeriphClockConfig(__RTC, ENABLE);

// Configure RTC

  RTC_DeInit();

// Display current time

  puts("Press D to set the date\n");
  puts("Press T to set the time\n");

  then = 0;

  for (;;)
  {
    if (keypressed())
    {
      switch (toupper(getch()))
      {
        case 'T' :
          printf("Enter UTC time (HH:MM:SS): ");
          gets(buf);
          sscanf(buf, "%d:%d:%d", &hour, &minute, &second);

          memset(&t_rtc, 0, sizeof(t_rtc));
          t_rtc.hours = hour;
          t_rtc.minutes = minute;
          t_rtc.seconds = second;
          RTC_SetTime(t_rtc);
          break;

        case 'D' :
          printf("Enter UTC date (YYYY MM DD): ");
          gets(buf);
          sscanf(buf, "%d %d %d", &year, &month, &day);

          memset(&d_rtc, 0, sizeof(d_rtc));
          d_rtc.century = year / 100;
          d_rtc.year = year % 100;
          d_rtc.month = month;
          d_rtc.day = day;
          RTC_SetDate(d_rtc);
          break;
      }
    }

    RTC_GetDate(BINARY, &d_rtc);
    RTC_GetTime(BINARY, &t_rtc);

// Get the date again if the current time is 00:00:00 (Midnight)

    if ((t_rtc.hours == 0) && (t_rtc.minutes == 0) && (t_rtc.seconds == 0))
      RTC_GetDate(BINARY, &d_rtc);

    now = time(NULL);

    if (now == then) continue;

    then = now;

    printf("%04d %02d %02d %02d:%02d:%02d %s", d_rtc.century*100 + d_rtc.year,
           d_rtc.month, d_rtc.day, t_rtc.hours, t_rtc.minutes, t_rtc.seconds,
           ctime(&now));
  }
}
