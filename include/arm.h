/* ARM microcontroller common definitions */

// $Id$

#ifndef _ARM_H
#define _ARM_H

#include <_ansi.h>

#define errno_r			(*(__errno()))

#ifndef TRUE
#define TRUE			1
#endif

#ifndef FALSE
#define FALSE			0
#endif

// Define ABI string

#ifdef __ARM_EABI__
#define	__ABI__			"EABI"
#else
#define __ABI__			"ELF"
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

// Trick linker into using our syscall functions

_BEGIN_STD_C

extern void __use_custom_syscalls(void);

_END_STD_C
#endif
