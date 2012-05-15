/* ARM microcontroller device specific definitions and header files */

// $Id$

#ifndef _CPU_H
#define _CPU_H

#include <_ansi.h>
#include <arm.h>
#include <device.h>
#include <gpiopins.h>
#include <leds.h>
#include <serial.h>

#include <LPC17xx.h>

#define CPUFREQ			SystemCoreClock

_BEGIN_STD_C

extern void cpu_init(unsigned long int frequency);

_END_STD_C
#endif
