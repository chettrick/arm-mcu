/* ARM microcontroller device specific definitions and header files */

// $Id$

#include <device.h>
#include <gpiopins.h>
#include <leds.h>
#include <serial.h>

#include <LPC17xx.h>

#define errno_r			(*(__errno()))

#ifndef TRUE
#define TRUE			1
#endif

#ifndef FALSE
#define FALSE			0
#endif

#define CPUFREQ			SystemCoreClock
#define DEFAULT_CPU_FREQ	100000000

#ifndef CONSOLE_PORT
#define CONSOLE_PORT		0
#endif

#ifdef INTEGER_STDIO
#define printf(...)		iprintf(__VA_ARGS__)
#define fprintf(...)		fiprintf(__VA_ARGS__)
#define sprintf(...)		siprintf(__VA_ARGS__)
#define snprintf(...)		sniprintf(__VA_ARGS__)
#define asprintf(...)		asiprintf(__VA_ARGS__)
#define asnprintf(...)		asniprintf(__VA_ARGS__)

#define scanf(...)		iscanf(__VA_ARGS__)
#define sscanf(...)		siscanf(__VA_ARGS__)
#define fscanf(...)		fiscanf(__VA_ARGS__)
#endif

extern void __use_custom_syscalls(void);
extern void cpu_init(unsigned long int frequency);
