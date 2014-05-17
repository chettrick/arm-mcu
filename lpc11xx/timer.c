// Copyright (C)2014, Philip Munts, President, Munts AM Corp.
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

#include <cpu.h>

// Check a parameter against a limit

#define CHECK_PARAMETER(parm, limit) if (parm >= limit) { errno_r = ENODEV; return -1; }

/******************************************************************************/

// Timer register offsets

#define TIMER_IR	0x000
#define TIMER_TCR	0x001
#define TIMER_TC	0x002
#define TIMER_PR	0x003
#define TIMER_PC	0x004
#define TIMER_MCR	0x005
#define TIMER_MR0	0x006
#define TIMER_MR1	0x007
#define TIMER_MR2	0x008
#define TIMER_MR3	0x009
#define TIMER_CCR	0x00A
#define TIMER_CR0	0x00B
#define TIMER_EMR	0x00F
#define TIMER_CTCR	0x01C
#define TIMER_PWMC	0x01D

// Timer register macros

#define IR		TIMERS[id][TIMER_IR]
#define TCR		TIMERS[id][TIMER_TCR]
#define TC		TIMERS[id][TIMER_TC]
#define PR		TIMERS[id][TIMER_PR]
#define PC		TIMERS[id][TIMER_PC]
#define MCR		TIMERS[id][TIMER_MCR]
#define MR0		TIMERS[id][TIMER_MR0]
#define MR1		TIMERS[id][TIMER_MR1]
#define MR2		TIMERS[id][TIMER_MR2]
#define MR3		TIMERS[id][TIMER_MR3]
#define MRn(n)		TIMERS[id][TIMER_MR0+n]
#define CCR		TIMERS[id][TIMER_CCR]
#define CR0		TIMERS[id][TIMER_CR0]
#define EMR		TIMERS[id][TIMER_EMR]
#define CTCR		TIMERS[id][TIMER_CTCR]
#define PWMC		TIMERS[id][TIMER_PWMC]

/******************************************************************************/

// This table maps a timer ID to its register block address

static uint32_t * const TIMERS[TIMER_ID_SENTINEL] =
{
  (uint32_t *) LPC_CT32B0_BASE,
  (uint32_t *) LPC_CT32B1_BASE,
};

// This table maps a timer ID to its bit in SYSAHBCLKCTRL

static const unsigned PWRBITS[TIMER_ID_SENTINEL] =
{
  1 << 9,
  1 << 10,
};

// This table maps a timer mode to a TCR register value

static const unsigned MODE_TO_TCR[TIMER_MODE_SENTINEL] =
{
  0x00,	// TIMER_MODE_DISABLED
  0x03,	// TIMER_MODE_RESET
  0x01,	// TIMER_MODE_PCLK
  0x01,	// TIMER_MODE_CAP0_RISING
  0x01,	// TIMER_MODE_CAP0_FALLING
  0x01,	// TIMER_MODE_CAP0_BOTH
};

// This table maps a timer mode to a CTCR register value

static const unsigned MODE_TO_CTCR[TIMER_MODE_SENTINEL] =
{
  0x00,	// TIMER_MODE_DISABLED
  0x00,	// TIMER_MODE_RESET
  0x00,	// TIMER_MODE_PCLK
  0x01,	// TIMER_MODE_CAP0_RISING
  0x02,	// TIMER_MODE_CAP0_FALLING
  0x03,	// TIMER_MODE_CAP0_BOTH
};

// This table maps a timer ID to a GPIO pin for CAP0

static const unsigned TIMER_TO_INPUT_PIN[TIMER_ID_SENTINEL] =
{
  PIO1_5,
  PIO1_0,
};

// This table maps a timer ID to an IOCON function setting for CAP0

static const unsigned TIMER_TO_INPUT_PIN_FUNC[TIMER_ID_SENTINEL] =
{
  2,
  3,
};

// This table maps a timer ID and match register to a GPIO pin for the MATn output

static const unsigned MATCH_TO_OUTPUT_PIN[TIMER_ID_SENTINEL][TIMER_MATCH_OUTPUTS] =
{
  { PIO1_6, PIO1_7, PIO0_1, PIO1_11 },
  { PIO1_1, PIO1_2, PIO1_3, PIO1_4  }
};

// This table maps a timer ID and match register to an IOCON function setting
// for the MATn output

static const unsigned MATCH_TO_OUTPUT_PIN_FUNC[TIMER_ID_SENTINEL][TIMER_MATCH_OUTPUTS] =
{
  { 2, 2, 2, 3 },
  { 3, 3, 3, 2 }
};

/******************************************************************************/

// Initialize the timer to a known state

int timer_init(unsigned id)
{
  CHECK_PARAMETER(id, TIMER_ID_SENTINEL);

  LPC_SYSCON->SYSAHBCLKCTRL |= PWRBITS[id];

  TCR = MODE_TO_TCR[TIMER_MODE_RESET];

  IR = 0;
  TCR = 0;
  TC = 0;
  PR = 0;
  PC = 0;
  MCR = 0;
  MR0 = 0;
  MR1 = 0;
  MR2 = 0;
  MR3 = 0;
  CCR = 0;
  CR0 = 0;
  EMR = 0;
  CTCR = 0;
  PWMC = 0;

  errno_r = 0;
  return 0;
}

/******************************************************************************/

// Configure the timer mode

int timer_configure_mode(unsigned id, unsigned mode)
{
  CHECK_PARAMETER(id, TIMER_ID_SENTINEL);
  CHECK_PARAMETER(mode, TIMER_MODE_SENTINEL);

  if (mode >= TIMER_MODE_CAP0_RISING)
  {
    gpio_configure_function(TIMER_TO_INPUT_PIN[id], TIMER_TO_INPUT_PIN_FUNC[id]);
  }

  CTCR = MODE_TO_CTCR[mode];
  TCR = MODE_TO_TCR[mode];

  errno_r = 0;
  return 0;
}

/******************************************************************************/

// Configure the prescaler value

int timer_configure_prescaler(unsigned id, unsigned divisor)
{
  CHECK_PARAMETER(id, TIMER_ID_SENTINEL);

  PR = divisor - 1;
  PC = 0;

  errno_r = 0;
  return 0;
}

/******************************************************************************/

// Configure a capture input

int timer_configure_capture(unsigned id, unsigned edge, bool intr)
{
  CHECK_PARAMETER(id, TIMER_ID_SENTINEL);
  CHECK_PARAMETER(edge, TIMER_CAPTURE_EDGE_SENTINEL);
  CHECK_PARAMETER(intr, 2);

  // Only allow the interrupt if an edge is enabled

  if ((edge == TIMER_CAPTURE_EDGE_DISABLED) && intr)
  {
    errno_r = EINVAL;
    return -1;
  }

  // Configure the capture input

  if (edge > TIMER_CAPTURE_EDGE_DISABLED)
  {
    gpio_configure_function(TIMER_TO_INPUT_PIN[id], TIMER_TO_INPUT_PIN_FUNC[id]);
  }

  CCR = edge | (intr << 2);

  errno_r = 0;
  return 0;
}

/******************************************************************************/

int timer_configure_match(unsigned id, unsigned m, unsigned action,
  bool intr, bool reset, bool stop)
{
  CHECK_PARAMETER(id, TIMER_ID_SENTINEL);
  CHECK_PARAMETER(m, TIMER_MATCH_OUTPUTS);
  CHECK_PARAMETER(action, TIMER_MATCH_OUTPUT_SENTINEL);
  CHECK_PARAMETER(intr, 2);
  CHECK_PARAMETER(reset, 2);
  CHECK_PARAMETER(stop, 2);

  if (action > TIMER_MATCH_OUTPUT_DISABLED)
  {
    gpio_configure_function(MATCH_TO_OUTPUT_PIN[id][m],
      MATCH_TO_OUTPUT_PIN_FUNC[id][m]);
  }

  EMR &= ~(3 << (m*2 + 4));
  EMR |= (action << (m*2 + 4));

  MCR &= ~(7 << (m*3));
  MCR |= (intr|(reset << 1)|(stop << 2)) << (m*3);

  errno_r = 0;
  return 0;
}

/******************************************************************************/

int timer_configure_match_value(unsigned id, unsigned m, unsigned n)
{
  CHECK_PARAMETER(id, TIMER_ID_SENTINEL);
  CHECK_PARAMETER(m, TIMER_MATCH_OUTPUTS);

  MRn(m) = n;

  errno_r = 0;
  return 0;
}
