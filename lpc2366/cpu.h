/* ARM microcontroller device specific definitions and header files */

// $Id$

extern unsigned long int CPUFREQ;

extern void cpu_init(unsigned long int frequency);

#include <device.h>
#include <interrupt.h>
#include <serial.h>

#include <LPC23XX.h>

#ifndef DEFAULT_CPU_FREQ
#ifdef REVISION_A
#define DEFAULT_CPU_FREQ	48000000
#else
#define DEFAULT_CPU_FREQ	72000000
#endif
#endif

#ifndef CONSOLE_PORT
#define CONSOLE_PORT		0
#endif
