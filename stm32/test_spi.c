/* Simple serial console I/O test program for the STM32 ARM MCU */

// $Id$

static const char revision[] = "$Id$";

#include <assert.h>
#include <cpu.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SPI_PORT 1

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

  serial_stdio(CONSOLE_PORT, 115200);

  puts("\033[H\033[2JSTM32 SPI Master Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", CPUFREQ, __VERSION__);

  if ((status = spimaster_init(SPI_PORT, 0, 281250, TRUE)))
  {
    fprintf(stderr, "ERROR: spimaster_init() failed at line %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

  for (;;)
  {
    printf("Enter a value to send: ");
    fflush(stdout);
    fflush(stdin);
    gets(buf);
    commandbyte = atoi(buf);

    if ((status = spimaster_transfer(SPI_PORT, &commandbyte, 1, &responsebyte, 1)))
    {
      fprintf(stderr, "ERROR: spimaster_transfer() failed at line %d, %s\n", status, strerror(errno));
      assert(FALSE);
    }

    printf("Response was %02X\n\n", responsebyte);
  }
}
