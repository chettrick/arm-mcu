/* ARM microcontroller device specific definitions and header files */

// $Id: cpu.h 3165 2011-10-17 10:55:40Z svn $

#include <arm.h>
#include <device.h>
#include <gpiopins.h>
#include <leds.h>
#include <serial.h>
#include <spi.h>
#include <stm32f4xx.h>

#define CPUFREQ			SystemCoreClock

#ifndef DEFAULT_CPU_FREQ
#ifdef stm32f407vg
#define DEFAULT_CPU_FREQ	168000000
#endif
#endif

#ifndef CONSOLE_PORT
#ifdef STM32F4_DISCOVERY
#define CONSOLE_PORT		"com2:115200,n,8,1"
#endif
#endif

extern void cpu_init(unsigned long int frequency);
