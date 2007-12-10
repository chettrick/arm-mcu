/* Initialize CPU core */

// $Id: cpu.c,v 1.2 2007-12-10 10:20:15 cvs Exp $

#include <cpu.h>
#include <stdio.h>
#include <string.h>

unsigned long int CPUFREQ;

void cpu_init(unsigned long int frequency)
{
  CPUFREQ = DEFAULT_CPU_FREQ;		// Not currently changeable
}
