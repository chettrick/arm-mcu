/* Initialize CPU core */

// $Id: cpu.c,v 1.1 2007-11-23 12:32:27 cvs Exp $

#include <cpu.h>
#include <stdio.h>
#include <string.h>

unsigned long int CPUFREQ;

void cpu_init(unsigned long int frequency)
{
  CPUFREQ = frequency;
}
