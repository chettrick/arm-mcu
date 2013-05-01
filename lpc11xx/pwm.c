/* Abstract services for controlling LPC11xx PWM outputs */

// $Id$

// Copyright (C)2013, Philip Munts, President, Munts AM Corp.
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
#include <errno.h>

// Initialize on of the 32-bit timers for PWM service
// We use match register 3 for setting the PWM period, per the user
// manual recommendation

int pwm_timer_init(unsigned timer, unsigned frequency)
{
  errno_r = 0;

  switch (timer)
  {
    case 0 :	// CT32B0
      LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 9);	// Enable peripheral clock
      LPC_TMR32B0->PR = 0;			// No prescaler
      LPC_TMR32B0->MCR = 0x00000400;		// Reset on match register 3
      LPC_TMR32B0->MR3 = SystemCoreClock/frequency;
      LPC_TMR32B0->CTCR = 0;			// Timer mode
      LPC_TMR32B0->TCR = 1;			// Enable counter/timer
      break;

    case 1 :	// CT32B1
      LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 10);	// Enable peripheral clock
      LPC_TMR32B1->PR = 0;			// No prescaler
      LPC_TMR32B1->MCR = 0x00000400;		// Reset on match register 3
      LPC_TMR32B1->MR3 = SystemCoreClock/frequency;
      LPC_TMR32B1->CTCR = 0;			// Timer mode
      LPC_TMR32B1->TCR = 1;			// Enable counter/timer
      break;

    default :
      errno_r = ENODEV;
      return -1;
  }

  return 0;
}

int pwm_init(unsigned channel, unsigned frequency)
{
  errno_r = 0;

  switch (channel)
  {
    case 0 :	// CT32B1_MAT0
      if (pwm_timer_init(0, frequency))
        return -1;

      LPC_TMR32B0->PWMC |= (1 << 0);		// Set PWMEN0
      LPC_TMR32B0->MR0 = 0xFFFFFFFF;		// Turn output off at first
      LPC_IOCON->PIO1_6 = 0x000000C2;		// Enable match output
      break;

    case 1 :	// CT32B1_MAT1
      if (pwm_timer_init(0, frequency))
        return -1;

      LPC_TMR32B0->PWMC |= (1 << 1);		// Set PWMEN1
      LPC_TMR32B0->MR1 = 0xFFFFFFFF;		// Turn output off at first
      LPC_IOCON->PIO1_7 = 0x000000C2;		// Enable match output
      break;

    case 2 :	// CT32B1_MAT2
      if (pwm_timer_init(0, frequency))
        return -1;

      LPC_TMR32B0->PWMC |= (1 << 2);		// Set PWMEN2
      LPC_TMR32B0->MR2 = 0xFFFFFFFF;		// Turn output off at first
      LPC_IOCON->PIO0_1 = 0x000000C2;		// Enable match output
      break;

    case 4 :	// CT32B1_MAT0
      if (pwm_timer_init(1, frequency))
        return -1;

      LPC_TMR32B1->PWMC |= (1 << 0);		// Set PWMEN0
      LPC_TMR32B1->MR0 = 0xFFFFFFFF;		// Turn output off at first
      LPC_IOCON->R_PIO1_1 = 0x000000C3;		// Enable match output
      break;

    case 5 :	// CT32B1_MAT1
      if (pwm_timer_init(1, frequency))
        return -1;

      LPC_TMR32B1->PWMC |= (1 << 1);		// Set PWMEN1
      LPC_TMR32B1->MR1 = 0xFFFFFFFF;		// Turn output off at first
      LPC_IOCON->R_PIO1_2 = 0x000000C3;		// Enable match output
      break;

    case 6 :	// CT32B1_MAT2
      if (pwm_timer_init(1, frequency))
        return -1;

      LPC_TMR32B1->PWMC |= (1 << 2);		// Set PWMEN2
      LPC_TMR32B1->MR2 = 0xFFFFFFFF;		// Turn output off at first
      LPC_IOCON->SWDIO_PIO1_3 = 0x000000C3;	// Enable match output
      break;

    default :
      errno_r = ENODEV;
      return -1;
  }

  return 0;
}

int pwm_set(unsigned channel, uint32_t value)
{
  errno_r = 0;

  switch (channel)
  {
    case 0 :	// CT32B0_MAT0
      LPC_TMR32B0->MR0 = value;
      break;

    case 1 :	// CT32B1_MAT1
      LPC_TMR32B0->MR1 = value;
      break;

    case 2 :	// CT32B2_MAT2
      LPC_TMR32B0->MR2 = value;
      break;

    // MR3 is used for setting the PWM period

    case 4 :	// CT32B1_MAT0
      LPC_TMR32B1->MR0 = value;
      break;

    case 5 :	// CT32B1_MAT1
      LPC_TMR32B1->MR1 = value;
      break;

    case 6 :	// CT32B1_MAT2
      LPC_TMR32B1->MR2 = value;
      break;

    // MR3 is used for setting the PWM period

    default :
      errno_r = ENODEV;
      return -1;
  }

  return 0;
}
