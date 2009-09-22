/* ARM microcontroller device specific definitions and header files */

// $Id$

extern unsigned long int CPUFREQ;

extern void cpu_init(unsigned long int frequency);

#include <device.h>
#include <io.h>
#include <serial.h>

#define DEFAULT_CPU_FREQ 48000000
