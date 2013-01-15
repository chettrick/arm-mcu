/* Initialize CPU core */

// $Id$

// Copyright (C)2013, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification,are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// * Neither the name of Munts AM Corp. nor the names of its contributors may
//   be used to endorse or promote products derived from this software without
//   specific prior written permission.
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

/* Initialize MAM--See Errata MAM.1 */

#ifdef REVISION_A
  MAMCR = 1;			// MAM functions partially enabled
  MAMTIM = 3;			// CPU clocks per fetch cycle
#else
  MAMCR = 2;			// MAM functions fully enabled
  MAMTIM = 4;			// CPU clocks per fetch cycle
#endif

/* Configure clock generators--See Errata PLL.1 and Flash.1 */

  SCS = 0x00000021;		// Turn on main oscillator, fast GPIO
  while (!(SCS & (1 << 6)));	// Wait for main oscillator startup

  CLKSRCSEL = 1;		// PLL source is main oscillator

  PLLCFG = 11;			// N=1, M=12 (Fin=12 MHz, Fref=12 MHz, Fcco=288 MHz)
  PLLCON = 1;			// Enable PLL
  PLLFEED = 0xAA;
  PLLFEED = 0x55;

  while (!(PLLSTAT & (1 << 26))); // Wait for PLL lock

#ifdef REVISION_A
  CCLKCFG = 5;			// CPU clock is Fcco/6 (48 MHz)
#else
  CCLKCFG = 3;			// CPU clock is Fcco/4 (72 MHz)
#endif
  USBCLKCFG = 5;		// USB clock is Fcco/6 (48 MHz)

  PLLCON = 3;			// Connect PLL
  PLLFEED = 0xAA;
  PLLFEED = 0x55;

#ifdef REVISION_A
  SystemCoreClock = 48000000;
#else
  SystemCoreClock = 72000000;
#endif
}

_BEGIN_STD_C

__attribute__ ((weak)) void SysTick_Handler(void)	// Satisfy linker
{
}

__attribute__ ((__interrupt__)) void Timer0ISR(void)
{
  SysTick_Handler();

  T0IR = 0x01;
  VICVectAddr = 0;
}

unsigned long int SysTick_Config(unsigned long int ticks)
{

/* Configure timer 0 */

  PCLKSEL0 &= 0xFFFFFFF3;			// PCLK_TIMER0 is CCLK/4

  T0TCR = 2;					// Reset timer 0
  T0TCR = 0;					// Release timer 0 reset
  T0PR = 0;					// Timer 0 precaler trips every PCLK
  T0CTCR = 0;					// Timer 0 increments every PCLK
  T0MR0 = ticks/4;				// Match when we reach tick count
  T0MCR = 3;					// Interrupt and reset on match

/* Configure timer 0 interrupt */

  DISABLE_INTERRUPTS(IRQ);

  VICIntSelect &= ~(1 << INT_TIMER0);		// Timer 0 uses IRQ
  VICVectPriority4 = 0;
  VICVectAddr4 = (unsigned long int) Timer0ISR;	// Timer 0 ISR address
  VICIntEnable = 1 << INT_TIMER0;		// Enable timer 0 interrupt

  ENABLE_INTERRUPTS(IRQ);

  T0TCR = 1;					// Start timer 0

  return 0;
}

_END_STD_C
