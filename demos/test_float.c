/* Simple floating point arithmetic test program MCU */

// $Id$

static const char revision[] = "$Id$";

#undef INTEGER_STDIO

#include <cpu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  float x, y;
  int z;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef CONSOLE_USB
  usb_serial_stdio(NULL);
  getch();
#else
  serial_stdio(CONSOLE_PORT);
#endif

  printf("\033[H\033[2J%s Floating Point Arithmetic Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s %s %s\n\n", SystemCoreClock, __COMPILER__, __VERSION__, __ABI__);

  x = 1.0;
  y = 2.0;
  z = x + y;

  printf("x is %f, y is %f, x+y is %f, z is %d\n", x, y, x+y, z);
  exit(0);
}
