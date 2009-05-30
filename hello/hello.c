/* Simple "Hello, world" application */

// $Id: hello.c,v 1.4 2009-05-30 07:40:41 cvs Exp $

#include <conio.h>
#include <cpu.h>
#include <stdio.h>

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);
  conio_init(0, 115200);

  puts("\033[H\033[2JHello, world\n");

  for (;;)
    putch(getch());
}
