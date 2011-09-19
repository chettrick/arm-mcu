/* Simple SPI master routines for STM32 */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <stdint.h>
#include <errno.h>
#undef errno
extern int errno;

// Map SPI port number to pointer to control structure

static SPI_TypeDef * const SPI_PORTS[MAX_SPI_PORTS] =
{
  SPI1,
  SPI2,
  SPI3,
};

/*****************************************************************************/

// Calculate the SPI clock prescaler for a given SPI clock rate.  Return an
//  error if the requested SPI clock rate isn't possible.

static int SPI_Clock_Prescaler(uint32_t port,
                               uint32_t speed,
                               uint32_t *prescaler)
{
  RCC_ClocksTypeDef RCC_Clocks;
  uint32_t PCLK;

// Get peripheral clock frequencies

  RCC_GetClocksFreq(&RCC_Clocks);

// Different SPI ports use PCLK1 or PCLK2 peripheral clock

  switch (port)
  {
    case 1 :
      PCLK = RCC_Clocks.PCLK2_Frequency;
      break;

    case 2 :
    case 3 :
      PCLK = RCC_Clocks.PCLK1_Frequency;
      break;

    default :
      errno = EINVAL;
      return 1;
  }

// Calculate SPI clock prescaler from desired SPI clock rate and PCLK rate

  if (speed == PCLK/256)
    *prescaler = SPI_BaudRatePrescaler_256;
  else if (speed == PCLK/128)
    *prescaler = SPI_BaudRatePrescaler_128;
  else if (speed == PCLK/64)
    *prescaler = SPI_BaudRatePrescaler_64;
  else if (speed == PCLK/32)
    *prescaler = SPI_BaudRatePrescaler_32;
  else if (speed == PCLK/16)
    *prescaler = SPI_BaudRatePrescaler_16;
  else if (speed == PCLK/8)
    *prescaler = SPI_BaudRatePrescaler_8;
  else if (speed == PCLK/4)
    *prescaler = SPI_BaudRatePrescaler_4;
  else if (speed == PCLK/2)
    *prescaler = SPI_BaudRatePrescaler_2;

// Only the above SPI clock rates are possible.  Others are errnoneous.

  else
  {
    errno = EINVAL;
    return 1;
  }

  return 0;
}

/*****************************************************************************/

int spimaster_init(uint32_t port,
                   uint32_t clockmode,
                   uint32_t speed,
                   uint32_t wordsize,
                   uint32_t bigendian)
{
  SPI_InitTypeDef  SPI_InitStructure;
  uint32_t prescaler;

// Validate parameters

  if ((port < 1) && (port > MAX_SPI_PORTS))
  {
    errno = EINVAL;
    return 1;
  }

  if (clockmode > 3)
  {
    errno = EINVAL;
    return 1;
  }

  if ((wordsize != 8) && (wordsize != 16))
  {
    errno = EINVAL;
    return 1;
  }

  if (bigendian > 1)
  {
    errno = EINVAL;
    return 1;
  }

// Get SPI clock prescaler

  if (SPI_Clock_Prescaler(port, speed, &prescaler))
    return 1;

// Initialize the SPI port

  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize =
    (wordsize == 8) ? SPI_DataSize_8b : SPI_DataSize_16b;
  SPI_InitStructure.SPI_CPOL = clockmode & 0x02;
  SPI_InitStructure.SPI_CPHA = clockmode & 0x01;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = prescaler;
  SPI_InitStructure.SPI_FirstBit = 
    bigendian ? SPI_FirstBit_MSB : SPI_FirstBit_LSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI_PORTS[port], &SPI_InitStructure);

// Enable SPI port

  SPI_Cmd(SPI_PORTS[port], ENABLE);
  return 0;
}
