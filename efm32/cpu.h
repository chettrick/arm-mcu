/* ARM microcontroller device specific definitions and header files */

// $Id$

#include <arm.h>
#include <device.h>
#include <gpiopins.h>
#include <leds.h>
#include <serial.h>

#include <efm32.h>
#include <efm32_acmp.h>
#include <efm32_adc.h>
#include <efm32_aes.h>
#include <efm32_chip.h>
#include <efm32_cmu.h>
#include <efm32_common.h>
#include <efm32_dac.h>
#include <efm32_dbg.h>
#include <efm32_dma.h>
#include <efm32_ebi.h>
#include <efm32_emu.h>
#include <efm32_gpio.h>
#include <efm32_i2c.h>
#include <efm32_int.h>
#include <efm32_lcd.h>
#include <efm32_lesense.h>
#include <efm32_letimer.h>
#include <efm32_leuart.h>
#include <efm32_mpu.h>
#include <efm32_msc.h>
#include <efm32_opamp.h>
#include <efm32_pcnt.h>
#include <efm32_prs.h>
#include <efm32_rmu.h>
#include <efm32_rtc.h>
#include <efm32_system.h>
#include <efm32_timer.h>
#include <efm32_usart.h>
#include <efm32_vcmp.h>
#include <efm32_wdog.h>

#define CPUFREQ			SystemCoreClock
#define DEFAULT_CPU_FREQ	32000000UL

#ifndef CONSOLE_PORT
#define CONSOLE_PORT		"com1:115200,n,8,1"
#endif

extern void cpu_init(unsigned long int frequency);
