/* ARM microcontroller device specific definitions and header files */

// $Id$

extern unsigned long int CPUFREQ;

extern void cpu_init(unsigned long int frequency);

#include <device.h>
#include <serial.h>
#include <stm32f10x.h>

#ifndef DEFAULT_CPU_FREQ
#ifdef MCU_stm32f100rb
#define DEFAULT_CPU_FREQ	24000000
#endif

#ifdef MCU_stm32f103rb
#define DEFAULT_CPU_FREQ	72000000
#endif
#endif

#ifndef CONSOLE_PORT
#ifdef BOARD_OLIMEX_STM32_P103
#define CONSOLE_PORT		2
#else
#define CONSOLE_PORT		1
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
