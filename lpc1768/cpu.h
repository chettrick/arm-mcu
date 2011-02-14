/* ARM microcontroller device specific definitions and header files */

// $Id$

extern unsigned long int CPUFREQ;

extern void cpu_init(unsigned long int frequency);

#include <device.h>
#include <serial.h>

#define DEFAULT_CPU_FREQ	100000000

#ifndef CONSOLE_PORT
#define CONSOLE_PORT		0
#endif
