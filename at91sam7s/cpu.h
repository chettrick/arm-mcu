/* ARM microcontroller device specific definitions and header files */

// $Id$

#ifndef _CPU_H
#define _CPU_H

#include <_ansi.h>
#include <arm.h>
#include <device.h>
#include <serial.h>
#include <leds.h>

#include <AT91SAM7S.h>

_BEGIN_STD_C

extern void cpu_init(unsigned long int frequency);

extern unsigned long int CPUFREQ;

_END_STD_C
#endif
