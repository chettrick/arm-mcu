/* Initialize CPU core */

// $Id: cpu.h,v 1.3 2007-11-21 08:08:58 cvs Exp $

extern unsigned long int CPUFREQ;

extern void cpu_init(unsigned long int frequency);

#ifdef MCU_at91sam7a3
#include <at91sam7a3/io.h>
#define DEFAULT_CPU_FREQ 48000000
#endif

#ifdef MCU_lpc2119
#include <lpc2119/io.h>
#include <lpc2119/interrupt.h>
#define DEFAULT_CPU_FREQ 58982400
#endif

#ifdef MCU_lpc2366
#include <lpc2366/io.h>
#include <lpc2366/interrupt.h>
#define DEFAULT_CPU_FREQ 48000000
#endif

#ifdef MCU_str912fa
#include <str912fa/io.h>
#include <str912fa/interrupt.h>
#define DEFAULT_CPU_FREQ 48000000
#endif
