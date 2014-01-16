/* Simple standard I/O test program */

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

#ifdef CONIO_STDIO
#error This program cannot use the lightweight console I/O library
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cpu.h>

int main(void)
{
  int i;
  char buf[256];
  int x, y;

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

  printf("\033[H\033[2J%s Standard I/O Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  puts(revision);
  printf("\nCPU Freq:%u Hz  Compiler:%s %s %s\n\n", (unsigned int) SystemCoreClock,
    __COMPILER__, __VERSION__, __ABI__);

// Test putch()

  for (i = 'A'; i < 'Z'; i++)
    putch(i);

  putch('\n');
  putch('\n');

// Test cputs()

  for (i = 0; i < 10; i++)
  {
    sprintf(buf, "The value of the variable i is currently, now, until the next iteration, %d\n", i);
    cputs(buf);
  }

// Test keypressed() and getch()

  cputs("\nPress ^C to continue: ");

  for (;;)
  {
    if (keypressed())
    {
      if (getch() == 3)
        break;
      else
        putch('.');
    }
  }

  putch('\n');
  putch('\n');

// Test cputs() and cgets()

  for (;;)
  {
    cputs("[cgets] Enter a string: ");
    cgets(buf, sizeof(buf));
    if (strlen(buf)) if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;
    if (!strcasecmp(buf, "next")) break;
    printf("[cgets] You entered %u bytes, '%s'\n\n", (unsigned) strlen(buf), buf);
  }

// Test putchar()

  putchar('\n');

  for (i = 'a'; i < 'z'; i++)
    putchar(i);

  putchar('\n');
  putchar('\n');

// Test printf() and fgets()

  for (;;)
  {
    printf("[fgets] Enter a string: ");
    fflush(stdout);
    fgets(buf, sizeof(buf), stdin);
    if (strlen(buf)) if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;
    if (!strcasecmp(buf, "next")) break;
    printf("[fgets] You entered %u bytes, '%s'\n\n", (unsigned) strlen(buf), buf);
  }

  putchar('\n');

// Test numeric input

  for (;;)
  {
    printf("Enter two numbers: ");
    fflush(stdout);

    fflush(stdin);
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d %d", &x, &y);
    printf("You entered %d and %d\n", x, y);

    if ((x == 0) && (y == 0)) break;
  }

// Test assert()

  assert(false);
}
