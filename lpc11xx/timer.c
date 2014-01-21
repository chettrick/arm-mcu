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
#define TIMER_CR1	0x00C
#define TIMER_EMR	0x00F
#define TIMER_CTCR	0x01C
#define TIMER_PWMC	0x01D

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
  1 << 10
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
  0x01,	// TIMER_MODE_CAP1_RISING
  0x01,	// TIMER_MODE_CAP1_FALLING
  0x01,	// TIMER_MODE_CAP1_BOTH
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
  0x05,	// TIMER_MODE_CAP1_RISING
  0x06,	// TIMER_MODE_CAP1_FALLING
  0x07,	// TIMER_MODE_CAP1_BOTH
};

// This table maps a capture clear setting to a CTCR register value

static const unsigned CAPTURE_CLEAR_TO_CTCR[TIMER_CAPTURE_CLEAR_SENTINEL] =
{
  0x00, // TIMER_CAPTURE_CLEAR_DISABLED
  0x10, // TIMER_CAPTURE_CLEAR_CAP0_RISING
  0x30, // TIMER_CAPTURE_CLEAR_CAP0_FALLING
  0x50, // TIMER_CAPTURE_CLEAR_CAP1_RISING
  0x70, // TIMER_CAPTURE_CLEAR_CAP1_FALLING
};

// This table maps a timer ID and mode to a GPIO pin

static const unsigned MODE_TO_PIN[TIMER_ID_SENTINEL][TIMER_MODE_SENTINEL] =
{
  { 0, 0, 0, PIO1_5, PIO1_5, PIO1_5, PIO2_11, PIO2_11, PIO2_11 },
  { 0, 0, 0, PIO1_0, PIO1_0, PIO1_0, PIO1_11, PIO1_11, PIO1_11 }
};

// This table maps a timer ID and mode to an IOCON function setting for the
// GPIO pin

static const unsigned MODE_TO_FUNC[TIMER_ID_SENTINEL][TIMER_MODE_SENTINEL] =
{
  { 0, 0, 0, 2, 2, 2, 2, 2, 2 },
  { 0, 0, 0, 3, 3, 3, 2, 2, 2 }
};

// This table maps a timer ID and capture input to a GPIO pin

static const unsigned CAP_TO_PIN[TIMER_ID_SENTINEL][TIMER_CAPTURE_INPUTS] =
{
  { PIO1_5, PIO2_11 },
  { PIO1_0, PIO1_11 }
};

// This table maps a timer ID and capture input to an IOCON function setting
// for the GPIO pin

static const unsigned CAP_TO_FUNC[TIMER_ID_SENTINEL][TIMER_CAPTURE_INPUTS] =
{
  { 2, 2 },
  { 3, 2 }
};

// This table maps a timer ID and capture clear mode to a GPIO pin

static const unsigned CLR_TO_PIN[TIMER_ID_SENTINEL][TIMER_CAPTURE_CLEAR_SENTINEL] =
{
  { 0, PIO1_5, PIO1_5, PIO2_11, PIO2_11 },
  { 0, PIO1_0, PIO1_0, PIO1_11, PIO1_11 }
};

// This table maps a timer ID and capture clear mode to an IOCON function
// setting for the GPIO pin

static const unsigned CLR_TO_FUNC[TIMER_ID_SENTINEL][TIMER_CAPTURE_CLEAR_SENTINEL] =
{
  { 0, 2, 2, 2, 2 },
  { 0, 3, 3, 2, 2 }
};

// This table maps a timer ID and match output to a GPIO pin

static const unsigned MATCH_TO_PIN[TIMER_ID_SENTINEL][TIMER_MATCH_OUTPUTS] =
{
  { PIO1_6, PIO1_7, PIO0_1, PIO1_11 },
  { PIO1_1, PIO1_2, PIO1_3, PIO1_4  }
};

// This table maps a timer ID and match output to an IOCON function setting
// for the GPIO pin

static const unsigned MATCH_TO_FUNC[TIMER_ID_SENTINEL][TIMER_MATCH_OUTPUTS] =
{
  { 2, 2, 2, 3 },
  { 3, 3, 3, 2 }
};

/******************************************************************************/

// Configure the timer mode

int timer_configure_mode(unsigned id, unsigned mode)
{
  CHECK_PARAMETER(id, TIMER_ID_SENTINEL);
  CHECK_PARAMETER(mode, TIMER_MODE_SENTINEL);

  LPC_SYSCON->SYSAHBCLKCTRL |= PWRBITS[id];

  if (mode >= TIMER_MODE_CAP0_RISING)
  {
    gpio_configure_function(MODE_TO_PIN[id][mode], MODE_TO_FUNC[id][mode]);
  }

  TIMERS[id][TIMER_TCR] = MODE_TO_TCR[mode];
  TIMERS[id][TIMER_CTCR] = MODE_TO_CTCR[mode];

  errno_r = 0;
  return 0;
}

/******************************************************************************/

// Configure the prescaler value

int timer_configure_prescaler(unsigned id, unsigned divisor)
{
  CHECK_PARAMETER(id, TIMER_ID_SENTINEL);

  TIMERS[id][TIMER_PR] = divisor - 1;

  errno_r = 0;
  return 0;
}

/******************************************************************************/

// Configure a capture input

int timer_configure_capture(unsigned id, unsigned cap, unsigned edge, bool intr)
{
  CHECK_PARAMETER(id, TIMER_ID_SENTINEL);
  CHECK_PARAMETER(cap, TIMER_CAPTURE_INPUTS);
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
    gpio_configure_function(CAP_TO_PIN[id][cap], CAP_TO_FUNC[id][cap]);
  }

  TIMERS[id][TIMER_CCR] &= ~(7 << (cap*3));
  TIMERS[id][TIMER_CCR] |= ((intr << 2) | edge) << (cap*3);

  errno_r = 0;
  return 0;
}

/******************************************************************************/

// Configure the capture clear mode

int timer_configure_capture_clear(unsigned id, unsigned mode)
{
  CHECK_PARAMETER(id, TIMER_ID_SENTINEL);
  CHECK_PARAMETER(mode, TIMER_CAPTURE_CLEAR_SENTINEL);

  if (mode > TIMER_CAPTURE_CLEAR_DISABLED)
  {
    gpio_configure_function(CLR_TO_PIN[id][mode], CLR_TO_FUNC[id][mode]);
  }

  TIMERS[id][TIMER_CTCR] &= 0xFFFFFF0F;
  TIMERS[id][TIMER_CTCR] |= CAPTURE_CLEAR_TO_CTCR[mode];

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
    gpio_configure_function(MATCH_TO_PIN[id][m], MATCH_TO_FUNC[id][m]);
  }

  TIMERS[id][TIMER_EMR] &= ~(3 << (m*2 + 4));
  TIMERS[id][TIMER_EMR] |= (action << (m*2 + 4));

  TIMERS[id][TIMER_MCR] &= ~(7 << (m*3));
  TIMERS[id][TIMER_MCR] |= (intr|(reset << 1)|(stop << 2)) << (m*3);

  errno_r = 0;
  return 0;
}

/******************************************************************************/

int timer_configure_match_value(unsigned id, unsigned m, unsigned n)
{
  CHECK_PARAMETER(id, TIMER_ID_SENTINEL);
  CHECK_PARAMETER(m, TIMER_MATCH_OUTPUTS);

  TIMERS[id][TIMER_MR0 + m] = n;

  errno_r = 0;
  return 0;
}
