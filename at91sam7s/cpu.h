/* ARM microcontroller device specific definitions and header files */

// $Id$

#include <arm.h>
#include <device.h>
#include <serial.h>
#include <leds.h>

#include <AT91SAM7S.h>

#ifndef DEFAULT_CPU_FREQ
#define DEFAULT_CPU_FREQ	48000000
#endif

#ifndef CONSOLE_PORT
#define CONSOLE_PORT		"com1:115200,n,8,1"
#endif

extern void cpu_init(unsigned long int frequency);
extern unsigned long int CPUFREQ;
