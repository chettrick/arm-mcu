/* ARM microcontroller device specific definitions and header files */

// $Id$

#ifndef _CPU_H
#define _CPU_H

#include <_ansi.h>
#include <arm.h>
#include <device.h>
#include <interrupt.h>
#include <leds.h>
#include <serial.h>

#include <LPC23xx.h>

#define DEFAULT_CPU_FREQ	0

_BEGIN_STD_C

extern unsigned long int SystemCoreClock;
extern void cpu_init(unsigned long int frequency);

// Emulate Cortex-M3 system tick timer

extern unsigned long int SysTick_Config(unsigned long int ticks);
extern void SysTick_Handler(void);

_END_STD_C
#endif
