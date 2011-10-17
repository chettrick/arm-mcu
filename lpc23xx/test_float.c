/* Simple floating point arithmetic test program for the LPC23xx ARM MCU */

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

  serial_stdio(CONSOLE_PORT);

  puts("\033[H\033[2JLPC23xx Floating Point Arithmetic Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", CPUFREQ, __VERSION__);

  x = 1.0;
  y = 2.0;
  z = x + y;

  printf("x is %f, y is %f, x+y is %f, z is %d\n", x, y, x+y, z);
  exit(0);
}
