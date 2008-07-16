/******************************************************************************/
/*                                                                            */
/*        Syscall support functions for newlib console I/O with stdio         */
/*                                                                            */
/******************************************************************************/

// $Id: syscalls.c,v 1.3 2008-07-16 18:55:11 cvs Exp $

#include <conio.h>
#include <cpu.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

extern char end[];
static char *heap_ptr;

void * _sbrk(ptrdiff_t incr)
{
  char  *base;

/* Initialize if first time through. */

  if (!heap_ptr) heap_ptr = end;

  base = heap_ptr;      /*  Point to end of heap.                       */
  heap_ptr += incr;     /*  Increase heap.                              */

  return base;          /*  Return pointer to start of new heap area.   */
}

int _open(const char *path, int flags, ...)
{
  return 1;
}

int _close(int fd)
{
  return 0;
}

int _fstat(int fd, struct stat *st)
{
  st->st_mode = S_IFCHR;
  return 0;
}

int isatty(int fd)
{
  return 1;
}

int _lseek(int fd, off_t pos, int whence)
{
  return 0;
}

int _read(int fd, char *buf, size_t cnt)
{
  *buf = getch();

  return 1;
}

int _write(int fd, const char *buf, size_t cnt)
{
  int i;

  for (i = 0; i < cnt; i++)
    putch(buf[i]);

  return cnt;
}

/*
 * Copyright (c) 1997 Kungliga Tekniska Höolan
 * (Royal Institute of Technology, Stockholm, Sweden). 
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 *
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 *
 * 3. Neither the name of the Institute nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE. 
 */

static int is_leap(unsigned y)
{
	y += 1900;
	return (y % 4) == 0 && ((y % 100) != 0 || (y % 400) == 0);
}

static time_t rep_timegm(struct tm *tm)
{
	static const unsigned ndays[2][12] ={
		{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
		{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
	time_t res = 0;
	unsigned i;

	if (tm->tm_mon > 12 ||
	    tm->tm_mon < 0 ||
	    tm->tm_mday > 31 ||
	    tm->tm_min > 60 ||
	    tm->tm_sec > 60 ||
	    tm->tm_hour > 24) {
		/* invalid tm structure */
		return 0;
	}
	
	for (i = 70; i < tm->tm_year; ++i)
		res += is_leap(i) ? 366 : 365;
	
	for (i = 0; i < tm->tm_mon; ++i)
		res += ndays[is_leap(tm->tm_year)][i];
	res += tm->tm_mday - 1;
	res *= 24;
	res += tm->tm_hour;
	res *= 60;
	res += tm->tm_min;
	res *= 60;
	res += tm->tm_sec;
	return res;
}

int _gettimeofday(struct timeval *ptimeval, void *ptimezone)
{
  RTC_DATE date;
  RTC_TIME time;
  struct tm tm;
  time_t now;

// Read current date and time from the RTC

  RTC_GetDate(BINARY, &date);
  RTC_GetTime(BINARY, &time);

// Get the date again if the current time is 00:00:00 (Midnight)

    if ((time.hours == 0) && (time.minutes == 0) && (time.seconds == 0))
      RTC_GetDate(BINARY, &date);

// Convert current date and time to time_t

  memset(&tm, 0, sizeof(struct tm));
  tm.tm_sec = time.seconds;
  tm.tm_min = time.minutes;
  tm.tm_hour = time.hours;
  tm.tm_mday = date.day;
  tm.tm_mon = date.month - 1;
  tm.tm_year = date.century*100 + date.year - 1900;
  now = rep_timegm(&tm);

// Convert current date and time to struct timeval

  memset(ptimeval, 0, sizeof(struct timeval));
  ptimeval->tv_sec = now;

  return 0;
}

/* Override fgets() in newlib with a version that does line editing */

char *fgets(char *s, int bufsize, void *f)
{
  cgets(s, bufsize);
  return s;
}
