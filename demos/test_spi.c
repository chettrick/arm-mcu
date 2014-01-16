/* Simple SPI master I/O test program */

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cpu.h>

#ifndef SPI_PORT
#ifdef OLIMEX_STM32_P103
#define SPI_PORT	1
#endif

#ifdef OLIMEX_STM32_P107
#define SPI_PORT	3
#endif

#ifdef STM32_VALUE_LINE_DISCOVERY
#define SPI_PORT	1
#endif

#ifdef W5200E01_M3
#define SPI_PORT	2
#endif
#endif

int main(void)
{
  int status;
  char buf[256];
  uint8_t commandbyte;
  uint8_t responsebyte;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef CONSOLE_SERIAL
  serial_stdio(CONSOLE_PORT);
#endif

#ifdef CONSOLE_SEMIHOSTING
  semihosting_stdio(CONSOLE_PORT)
#endif

#ifdef CONSOLE_USB
  usb_serial_stdio(NULL);
  getch();
#endif

  printf("\033[H\033[2J%s SPI Master Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  puts(revision);
  printf("\nCPU Freq:%u Hz  Compiler:%s %s %s\n\n", (unsigned int) SystemCoreClock,
    __COMPILER__, __VERSION__, __ABI__);

  if ((status = spi_master_init(SPI_PORT, 8, 0, 281250, SPI_MSBFIRST)))
  {
    printf("ERROR: spi_master_init() failed at line %d, %s\n", status, strerror(errno));
    exit(1);
  }

  for (;;)
  {
    printf("Enter a value to send: ");

    gets(buf);
    commandbyte = atoi(buf);

    if ((status = spi_master_transfer(SPI_PORT, &commandbyte, 1, &responsebyte, 1)))
    {
      printf("ERROR: spi_master_transfer() failed at line %d, %s\n", status, strerror(errno));
      exit(1);
    }

    printf("Response was %02X\n\n", responsebyte);
  }
}
