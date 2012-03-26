/* ARM microcontroller device specific definitions and header files */

// $Id$

#include <arm.h>
#include <device.h>
#include <gpiopins.h>
#include <leds.h>
#include <serial.h>

#include <LPC17xx.h>

#define CPUFREQ			SystemCoreClock
#define DEFAULT_CPU_FREQ	100000000

#ifndef CONSOLE_PORT
#define CONSOLE_PORT		"com1:115200,n,8,1"
#endif

extern void cpu_init(unsigned long int frequency);
