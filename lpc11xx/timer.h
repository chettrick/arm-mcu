// LPC11xx timer services

// $Id$

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

#ifndef _TIMER_H
#define _TIMER_H

_BEGIN_STD_C

#define TIMER_MATCH_OUTPUTS	4

// Enumeration types

typedef enum
{
  CT32B0,
  CT32B1,
  TIMER_ID_SENTINEL
} timer_id_t;

typedef enum
{
  TIMER_MODE_DISABLED,
  TIMER_MODE_RESET,
  TIMER_MODE_PCLK,
  TIMER_MODE_CAP0_RISING,
  TIMER_MODE_CAP0_FALLING,
  TIMER_MODE_CAP0_BOTH,
  TIMER_MODE_SENTINEL
} timer_mode_t;

typedef enum
{
  TIMER_CAPTURE_EDGE_DISABLED,
  TIMER_CAPTURE_EDGE_CAP0_RISING,
  TIMER_CAPTURE_EDGE_CAP0_FALLING,
  TIMER_CAPTURE_EDGE_CAP0_BOTH,
  TIMER_CAPTURE_EDGE_SENTINEL
} timer_capture_edge_t;

typedef enum
{
  TIMER_MATCH_OUTPUT_DISABLED,
  TIMER_MATCH_OUTPUT_CLEAR,
  TIMER_MATCH_OUTPUT_SET,
  TIMER_MATCH_OUTPUT_TOGGLE,
  TIMER_MATCH_OUTPUT_SENTINEL
} timer_match_output_action_t;

// Function prototypes

int timer_init(unsigned id);

int timer_configure_mode(unsigned id, unsigned mode);

int timer_configure_prescaler(unsigned id, unsigned divisor);

int timer_configure_capture(unsigned id, unsigned edge, bool intr);

int timer_configure_match(unsigned id, unsigned m, unsigned action,
  bool intr, bool reset, bool stop);

int timer_configure_match_value(unsigned id, unsigned m, unsigned n);

// Allow direct access to certain counter registers

#define TMR32B0TC	LPC_TMR32B0->TC
#define TMR32B0PC	LPC_TMR32B0->PC
#define TMR32B0CR0	LPC_TMR32B0->CR0
#define TMR32B0CR1	LPC_TMR32B0->CR1

#define TMR32B1TC	LPC_TMR32B1->TC
#define TMR32B1PC	LPC_TMR32B1->PC
#define TMR32B1CR0	LPC_TMR32B1->CR0
#define TMR32B1CR1	LPC_TMR32B1->CR1

_END_STD_C
#endif
