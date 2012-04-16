/* ARM microcontroller device specific definitions and header files */

// $Id$

#ifndef _CPU_H
#define _CPU_H

#include <_ansi.h>

_BEGIN_STD_C

#include <arm.h>
#include <device.h>
#include <interrupt.h>
#include <leds.h>
#include <serial.h>

#include <LPC23xx.h>

#ifndef DEFAULT_CPU_FREQ
#ifdef REVISION_A
#define DEFAULT_CPU_FREQ	48000000
#else
#define DEFAULT_CPU_FREQ	72000000
#endif
#endif

#ifndef CONSOLE_PORT
#define CONSOLE_PORT		"com1:115200,n,8,1"
#endif

extern void cpu_init(unsigned long int frequency);
extern unsigned long int CPUFREQ;

_END_STD_C
#endif
