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

#include <string.h>

#include <cpu.h>

int csprintf(char *out, const char *format, ...);

/* Lightweight alternative to newlib errno structure */

int lightweight_errno;

/* Lightweight alternative to newlib atoi() */

int lightweight_atoi(const char *s)
{
  int negative = false;
  int x = 0;

  if (*s == '-')
  {
    negative = true;
    s++;
  }

  while (*s)
  {
    char c = *s++;

    if ((c >= '0') && (c <= '9'))
      x = x*10 + c - '0';
    else
      break;
  }

  if (negative)
    x = -x;

  return x;
}

/* Lightweight alternative to newlib exit() */

void lightweight_exit(int status)
{
  for (;;);
}

/* Lightweight alternative to newlib strerror() */

char lightweight_strerrno_buf[20];

char *lightweight_strerror(int e)
{
  memset(lightweight_strerrno_buf, 0, sizeof(lightweight_strerrno_buf));
  csprintf(lightweight_strerrno_buf, "errno=%d", e);
  return lightweight_strerrno_buf;
}

/* Certain functions in libgcc call abort(), the newlib version of which */
/* uses the heap and global reentrancy structure.  So we replace it with */
/* our own trivial abort() implementation here.                          */

void abort(void)
{
  for (;;);
}

/* The following odd constructs cause the GNU linker ld to issue warnings if  */
/* the Newlib global reentrancy structure (_impure_ptr) is linked, or if the  */
/* heap is being used.  Either of these mean an unexpected amount of RAM will */
/* be consumed, and may cause the system to run out of memory.                */

static const char impure_ptr_warning[] __attribute__((section(".gnu.warning._impure_ptr"))) =
  "\n\nDANGER: newlib reentrancy structure linked: >1K RAM consumed\n";

static const char sbrk_warning[] __attribute__((section(".gnu.warning._sbrk"))) =
  "\n\nDANGER: newlib is using the heap\n";

/********** END OF PHILIP MUNTS' COPYRIGHTED CODE IN THIS FILE **********/

/*
	Copyright 2001, 2002 Georges Menie (www.menie.org)
	stdarg version contributed by Christian Ettinger

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

static void printchar(char **str, int c)
{
	if (str) {
		**str = c;
		++(*str);
	}
	else putch(c);
}

#define PAD_RIGHT 1
#define PAD_ZERO 2

static int prints(char **out, const char *string, int width, int pad)
{
	register int pc = 0, padchar = ' ';

	if (width > 0) {
		register int len = 0;
		register const char *ptr;
		for (ptr = string; *ptr; ++ptr) ++len;
		if (len >= width) width = 0;
		else width -= len;
		if (pad & PAD_ZERO) padchar = '0';
	}
	if (!(pad & PAD_RIGHT)) {
		for ( ; width > 0; --width) {
			printchar (out, padchar);
			++pc;
		}
	}
	for ( ; *string ; ++string) {
		printchar (out, *string);
		++pc;
	}
	for ( ; width > 0; --width) {
		printchar (out, padchar);
		++pc;
	}

	return pc;
}

/* the following should be enough for 32 bit int */
#define PRINT_BUF_LEN 12

static int printi(char **out, int i, int b, int sg, int width, int pad, int letbase)
{
	char print_buf[PRINT_BUF_LEN];
	register char *s;
	register int t, neg = 0, pc = 0;
	register unsigned int u = i;

	if (i == 0) {
		print_buf[0] = '0';
		print_buf[1] = '\0';
		return prints (out, print_buf, width, pad);
	}

	if (sg && b == 10 && i < 0) {
		neg = 1;
		u = -i;
	}

	s = print_buf + PRINT_BUF_LEN-1;
	*s = '\0';

	while (u) {
		t = u % b;
		if( t >= 10 )
			t += letbase - '0' - 10;
		*--s = t + '0';
		u /= b;
	}

	if (neg) {
		if( width && (pad & PAD_ZERO) ) {
			printchar (out, '-');
			++pc;
			--width;
		}
		else {
			*--s = '-';
		}
	}

	return pc + prints (out, s, width, pad);
}

static int print(char **out, const char *format, va_list args )
{
	register int width, pad;
	register int pc = 0;
	char scr[2];

	for (; *format != 0; ++format) {
		if (*format == '%') {
			++format;
			width = pad = 0;
			if (*format == '\0') break;
			if (*format == '%') goto out;
			if (*format == '-') {
				++format;
				pad = PAD_RIGHT;
			}
			while (*format == '0') {
				++format;
				pad |= PAD_ZERO;
			}
			for ( ; *format >= '0' && *format <= '9'; ++format) {
				width *= 10;
				width += *format - '0';
			}
			if( *format == 's' ) {
				register char *s = (char *)va_arg( args, int );
				pc += prints (out, s?s:"(null)", width, pad);
				continue;
			}
			if( *format == 'd' ) {
				pc += printi (out, va_arg( args, int ), 10, 1, width, pad, 'a');
				continue;
			}
			if( *format == 'x' ) {
				pc += printi (out, va_arg( args, int ), 16, 0, width, pad, 'a');
				continue;
			}
			if( *format == 'X' ) {
				pc += printi (out, va_arg( args, int ), 16, 0, width, pad, 'A');
				continue;
			}
			if( *format == 'u' ) {
				pc += printi (out, va_arg( args, int ), 10, 0, width, pad, 'a');
				continue;
			}
			if( *format == 'c' ) {
				/* char are converted to int then pushed on the stack */
				scr[0] = (char)va_arg( args, int );
				scr[1] = '\0';
				pc += prints (out, scr, width, pad);
				continue;
			}
		}
		else {
		out:
			printchar (out, *format);
			++pc;
		}
	}
	if (out) **out = '\0';
	va_end( args );
	return pc;
}

int cprintf(const char *format, ...)
{
        va_list args;

        va_start( args, format );
        return print( 0, format, args );
}

int csprintf(char *out, const char *format, ...)
{
        va_list args;

        va_start( args, format );
        return print( &out, format, args );
}

//
// Reduced version of scanf (%d, %x, %c, %n are supported)
// %d dec integer (E.g.: 12)
// %x hex integer (E.g.: 0xa0)
// %b bin integer (E.g.: b1010100010)
// %n hex, de or bin integer (e.g: 12, 0xa0, b1010100010)
// %c any character
//

int csscanf(const char* str, const char* format, ...)
{
	va_list ap;
	int value, tmp;
	int count;
	int pos;
	char neg, fmt_code;

	va_start(ap, format);

	for (count = 0; *format != 0 && *str != 0; format++, str++)
	{
		while (*format == ' ' && *format != 0)
			format++;
		if (*format == 0)
			break;

		while (*str == ' ' && *str != 0)
			str++;
		if (*str == 0)
			break;

		if (*format == '%')
		{
			format++;
			if (*format == 'n')
			{
                if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
                {
                    fmt_code = 'x';
                    str += 2;
                }
                else
                if (str[0] == 'b')
                {
                    fmt_code = 'b';
                    str++;
                }
                else
                    fmt_code = 'd';
			}
			else
				fmt_code = *format;

			switch (fmt_code)
			{
			case 'x':
			case 'X':
				for (value = 0, pos = 0; *str != 0; str++, pos++)
				{
					if ('0' <= *str && *str <= '9')
						tmp = *str - '0';
					else
					if ('a' <= *str && *str <= 'f')
						tmp = *str - 'a' + 10;
					else
					if ('A' <= *str && *str <= 'F')
						tmp = *str - 'A' + 10;
					else
						break;

					value *= 16;
					value += tmp;
				}
				if (pos == 0)
					return count;
				*(va_arg(ap, int*)) = value;
				count++;
				break;

            case 'b':
				for (value = 0, pos = 0; *str != 0; str++, pos++)
				{
					if (*str != '0' && *str != '1')
                        break;
					value *= 2;
					value += *str - '0';
				}
				if (pos == 0)
					return count;
				*(va_arg(ap, int*)) = value;
				count++;
				break;

			case 'd':
				if (*str == '-')
				{
					neg = 1;
					str++;
				}
				else
					neg = 0;
				for (value = 0, pos = 0; *str != 0; str++, pos++)
				{
					if ('0' <= *str && *str <= '9')
						value = value*10 + (int)(*str - '0');
					else
						break;
				}
				if (pos == 0)
					return count;
				*(va_arg(ap, int*)) = neg ? -value : value;
				count++;
				break;

			case 'c':
				*(va_arg(ap, char*)) = *str;
				count++;
				break;

			default:
				return count;
			}
		}
		else
		{
			if (*format != *str)
				break;
		}
	}

	va_end(ap);

	return count;
}
