/* CPU initialization functions for the AT91SAM7S ARM MCU */

// $Id$

// Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

static const char revision[] = "$Id$";

#include <cpu.h>

unsigned long int SystemCoreClock;

void cpu_init(unsigned long int frequency)
{

/* Enable user reset on -NRST */

  *AT91C_RSTC_RMR	= 0xA5000001;

/* Configure watchdog timer */

  *AT91C_WDTC_WDMR	= AT91C_WDTC_WDDIS;	// Disable watchdog timer for now

/* Configure clock generators for 18.432 MHz crystal, 96 MHz PLL clock, and 48 MHz master clock */

  *AT91C_CKGR_MOR	= 0x0000FF01;		// Enable main oscillator
  while (!(*AT91C_PMC_SR & AT91C_PMC_MOSCS)); 	// Wait for main oscillator startup

  *AT91C_CKGR_PLLR	= 0x10FA3F30;		// Configure PLL (USBDIV=2, MUL=250, PLLCOUNT=63, DIV=48)
  while (!(*AT91C_PMC_SR & AT91C_PMC_LOCK)); 	// Wait for PLL to lock

  *AT91C_PMC_MCKR	= AT91C_PMC_PRES_CLK_2;	// Master clock divider is 2
  while (!(*AT91C_PMC_SR & AT91C_PMC_MCKRDY)); 	// Wait for master clock ready

  *AT91C_PMC_MCKR	= AT91C_PMC_PRES_CLK_2 | AT91C_PMC_CSS_PLL_CLK;	// Master clock source is PLL
  while (!(*AT91C_PMC_SR & AT91C_PMC_MCKRDY)); 	// Wait for master clock ready

  SystemCoreClock = 48000000;
}

// Emulate Cortex-M3 system tick timer

_BEGIN_STD_C

#include "aic.h"
#include "pit.h"

__attribute__ ((weak)) void SysTick_Handler(void)	// Satisfy linker
{
}

__attribute__ ((__interrupt__)) void TimerISR(void)
{
  SysTick_Handler();

  *AT91C_AIC_EOICR = *AT91C_PITC_PIVR;	// Acknowledge interrupt
}

unsigned long int SysTick_Config(unsigned long int ticks)
{
  unsigned long int rate = SystemCoreClock/ticks;

/* Configure timer to interrupt specified times per second */

  PIT_Init(1000000/rate, SystemCoreClock/1000000);
  PIT_EnableIT();
  PIT_Enable();

/* Configure timer interrupt */

  AIC_ConfigureIT(AT91C_ID_SYS, AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL, TimerISR);
  AIC_EnableIT(AT91C_ID_SYS);

  return 0;
}

_END_STD_C
