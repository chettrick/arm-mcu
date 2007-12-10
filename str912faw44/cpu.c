/* Initialize CPU core */

// $Id: cpu.c,v 1.3 2007-12-10 12:06:55 cvs Exp $

#include <cpu.h>

unsigned long int CPUFREQ;

void cpu_init(unsigned long int frequency)
{
  CPUFREQ = DEFAULT_CPU_FREQ;		// Not currently changeable

  SCU_CLKCNTR = 0x00020002;		// Reset SCU_CLKCNTR register

  SCU_PLLCONF = 0x0003C019;		// P=3, N=192, M=25
  SCU_PLLCONF = 0x000BC019;		// Enable PLL

  while ((SCU_SYSSTATUS & 0x01) == 00);	// Wait for PLL lock

  SCU_CLKCNTR &= 0xFFFFFFFC;		// Switch master clock source to PLL
}
