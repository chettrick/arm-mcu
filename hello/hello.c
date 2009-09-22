/* Simple "Hello, world" application */

// $Id$

#include <cpu.h>
#include <stdio.h>

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);

#ifdef CONSOLE_USB
  usb_serial_stdio();
  getch();
#else
  serial_stdio(CONSOLE_PORT, 115200);
#endif

  puts("\033[H\033[2JHello, world\n");

  for (;;)
    putch(getch());
}
