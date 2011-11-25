/* ARM microcontroller device specific definitions and header files */

// $Id: cpu.h 3165 2011-10-17 10:55:40Z svn $

#include <device.h>
#include <gpiopins.h>
#include <leds.h>
#include <serial.h>
#include <spi.h>
#include <stm32f4xx.h>

#define errno_r			(*(__errno()))

#ifndef TRUE
#define TRUE			1
#endif

#ifndef FALSE
#define FALSE			0
#endif

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
