/* Simple "Hello, world" application */

// $Id: hello.c,v 1.3 2008-07-01 19:15:40 cvs Exp $

#include <conio.h>
#include <cpu.h>
#include <stdio.h>

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);
  conio_init(0, 19200);

  puts("\033[H\033[2JHello, world\n");

  for (;;)
    putch(getch());
}
