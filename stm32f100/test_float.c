/* Simple floating point arithmetic test program for the STM32F100 ARM MCU */

// $Id: test_float.c 2433 2011-03-05 16:42:34Z svn $

static const char revision[] = "$Id: test_float.c 2433 2011-03-05 16:42:34Z svn $";

#include <cpu.h>
#include <stdio.h>
#include <string.h>

#ifndef __ARM_EABI__
#error arm-elf-gcc does not support Cortex-M3 floating point correctly! Use an EABI toolchain.
#endif

int main(void)
{
  float x, y;
  int z;

  cpu_init(DEFAULT_CPU_FREQ);

  serial_stdio(CONSOLE_PORT, 115200);

  puts("\033[H\033[2JSTM32F100 Floating Point Arithmetic Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", CPUFREQ, __VERSION__);

  x = 1.0;
  y = 2.0;
  z = x + y;

  printf("x is %f, y is %f, x+y is %f, z is %d\n", x, y, x+y, z);
}
