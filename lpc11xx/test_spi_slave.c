/* LPC11xx SPI slave test program */

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

#include <cpu.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <conio.h>

typedef enum
{
  FRAMING_STATE_IDLE = 0,
  FRAMING_STATE_FRAME = 1,
} framing_state_t;

int main(void)
{
  framing_state_t state = FRAMING_STATE_IDLE;
  char c;
  char inbuf[256];
  char outbuf[256];
  char *inptr;
  char *outptr = NULL;
  int outcount = 0;
  int counter = 0;

  cpu_init(DEFAULT_CPU_FREQ);
  conio_init(CONSOLE_PORT);

  if (spislave_init(0, 8, 3, SPI_MSBFIRST))
  {
    printf("ERROR: spislave_init() failed, %s\n", strerror(errno));
    exit(0);
  }

  memset(inbuf, 0, sizeof(inbuf));
  inptr = inbuf;

  for (;;)
  {
if (keypressed()) { printf("SR is %08X\n", LPC_SSP0->SR); getch(); }

    // Check for data from SPI master

    if (!(LPC_SSP0->SR & 0x04))
      continue;

    // Read byte from SPI master

    c = LPC_SSP0->DR;

    switch (state)
    {
      case FRAMING_STATE_IDLE :
        if (c == ':')
        {
          state = FRAMING_STATE_FRAME;
        }
        break;

      case FRAMING_STATE_FRAME :
        if (c == ';')
        {
          memset(inbuf, 0, sizeof(inbuf));
          inptr = inbuf;
          state = FRAMING_STATE_IDLE;

          memset(outbuf, 0, sizeof(outbuf));
          sprintf(outbuf, "This is a test. Number %d\n", counter++);
          outptr = outbuf;
          outcount = 40;

          // Start loading the response into the SPI transmit FIFO

          while ((LPC_SSP0->SR & 0x02) && (outcount > 0))
          {
            LPC_SSP0->DR = *outptr++;
            outcount--;
          }
        }
        else
          *inptr++ = c;
        break;
    }

    if (outcount)
    {
      while ((LPC_SSP0->SR & 0x02) && (outcount > 0))
      {
        LPC_SSP0->DR = *outptr++;
        outcount--;
      }
    }
  }
}
