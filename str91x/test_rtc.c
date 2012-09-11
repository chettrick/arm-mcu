/* Simple real time clock test program for the STR91x ARM MCU */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef CONSOLE_CONIO
#include <conio.h>
#endif

int main(void)
{
  RTC_TIME t_rtc;
  RTC_DATE d_rtc;
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
          fflush(stdout);

          scanf("%d:%d:%d", &hour, &minute, &second);

          memset(&t_rtc, 0, sizeof(t_rtc));
          t_rtc.hours = hour;
          t_rtc.minutes = minute;
          t_rtc.seconds = second;
          RTC_SetTime(t_rtc);
          break;

        case 'D' :
          printf("Enter UTC date (YYYY MM DD): ");
          fflush(stdout);

          scanf("%d %d %d", &year, &month, &day);

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
