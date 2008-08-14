/* Simple real time clock test program */

// $Id: test_rtc.c,v 1.3 2008-08-14 20:08:18 cvs Exp $

#include <cpu.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(void)
{
  char c;
  char buf[32];
  RTC_TIME t_rtc;
  RTC_DATE d_rtc;
  int year, month, day, hour, minute, second;
  time_t t_unix;

  cpu_init(DEFAULT_CPU_FREQ);
  serial_stdio(0, 19200);

  puts("\033[H\033[2JSTR912FAW44 Real Time Clock Test (" __DATE__ " " __TIME__ ")\n");

// Turn on RTC peripheral clock

  SCU_APBPeriphClockConfig(__RTC, ENABLE);

// Configure RTC

  RTC_DeInit();

// Display current time

  puts("Press D to set the date\n");
  puts("Press T to set the time\n");

  for (;;)
  {
    if (keypressed())
    {
      switch (toupper(getch()))
      {
        case 'T' :
          printf("Enter UTC time (HH:MM:SS): ");
          fflush(stdout);

//          fgets(buf, sizeof(buf), stdin);
//          sscanf(buf, "%d:%d:%d\n", &hour, &minute, &second);
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

//          fgets(buf, sizeof(buf), stdin);
//          sscanf(buf, "%d %d %d\n", &year, &month, &day);
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

    t_unix = time(NULL);

    printf("%04d %02d %02d %02d:%02d:%02d %s", d_rtc.century*100 + d_rtc.year,
           d_rtc.month, d_rtc.day, t_rtc.hours, t_rtc.minutes, t_rtc.seconds,
           ctime(&t_unix));
  }  
}
