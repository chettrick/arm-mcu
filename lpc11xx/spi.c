#include <cpu.h>
#include <errno.h>

#define MAX_SPI_PORTS		2

int spi_slave_init(uint32_t port,
                  uint32_t wordsize,
                  uint32_t clockmode,
                  uint32_t bitorder)
{
  errno_r = 0;

// Validate parameters

  if (port >= MAX_SPI_PORTS)
  {
    errno_r = ENODEV;
    return __LINE__ - 3;
  }

  if ((wordsize < 4) || (wordsize > 16))
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if (clockmode > 3)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if (bitorder != SPI_MSBFIRST) // LPC11xx doesn't support LSB first
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  switch (port)
  {
    case 0 :
      // Configure SSP0 pins

      LPC_IOCON->PIO0_2 = 0x00000031;
      LPC_IOCON->PIO0_6 = 0x00000032;
      LPC_IOCON->PIO0_8 = 0x00000001;
      LPC_IOCON->PIO0_9 = 0x00000031;

      LPC_IOCON->SCK_LOC = 0x2;			// SCLK0 on PIO0_6

      // Enable SSP0 clock

      LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 11);   // Enable SSP0

      // Set SSP0 peripheral clock divider

      LPC_SYSCON->SSP0CLKDIV = 1;

      // Let SSP0 out of reset

      LPC_SYSCON->PRESETCTRL |= (1 << 0);

      // Configure SSP0

      LPC_SSP0->CR0 = (wordsize - 1) | (clockmode << 6);
      LPC_SSP0->CR1 = 0x00000006;
      break;

    case 1 :
      errno_r = ENODEV;				// SSP1 is not pinned out
      return __LINE__ - 1;
      break;
  }

  return 0;
}
