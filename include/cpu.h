/* Initialize CPU core */

// $Id$

extern unsigned long int CPUFREQ;

extern void cpu_init(unsigned long int frequency);

#ifdef MCU_at91sam7s256
#include <at91sam7s256/io.h>
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

#ifdef MCU_str912faw44
#include <str912faw44/device.h>
#include <str912faw44/interrupt.h>
#include <str912faw44/serial.h>
#include <str912faw44/FWLib/91x_lib.h>
#include <str912faw44/FWLib/91x_it.h>
#include <str912faw44/usb_serial/usb_serial.h>
#define DEFAULT_CPU_FREQ 48000000
#endif

#ifdef MCU_stm32f103
#include <stm32f103/FWLib/stm32f10x_lib.h>
#include <stm32f103/FWLib/stm32f10x_it.h>
#define DEFAULT_CPU_FREQ 72000000
#endif
