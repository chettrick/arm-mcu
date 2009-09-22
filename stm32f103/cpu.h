/* ARM microcontroller device specific definitions and header files */

// $Id$

extern unsigned long int CPUFREQ;

extern void cpu_init(unsigned long int frequency);

#include <device.h>
#include <serial.h>
#include <FWLib/stm32f10x_lib.h>
#include <FWLib/stm32f10x_it.h>

#ifndef DEFAULT_CPU_FREQ
#define DEFAULT_CPU_FREQ	72000000
#endif

#ifndef CONSOLE_PORT
#define CONSOLE_PORT		2
#endif
