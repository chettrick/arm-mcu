/* ARM microcontroller device specific definitions and header files */

// $Id$

extern unsigned long int CPUFREQ;

extern void cpu_init(unsigned long int frequency);

#include <device.h>
#include <interrupt.h>
#include <serial.h>
#include <usb_serial/usb_serial.h>
#include <FWLib/91x_lib.h>
#include <FWLib/91x_it.h>

#ifndef DEFAULT_CPU_FREQ
#define DEFAULT_CPU_FREQ	48000000
#endif

#ifndef CONSOLE_PORT
#define CONSOLE_PORT		0
#endif
