/* Simple SPI master routines for STM32F1 */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <errno.h>

#define MAX_SPI_PORTS		3

// Map SPI port number to control structure

static SPI_TypeDef * const SPI_PORTS[MAX_SPI_PORTS] =
{
  SPI1,
  SPI2,
  SPI3,
};

#define SPIx			(SPI_PORTS[port-1])

// Map SPI port number to GPIO pin for NSS.  We manipulate NSS via GPIO bit
// banding, because the STM32F1 SPI controller doesn't automatically assert
// and deassert NSS.

static uint32_t * const SPI_NSS_PIN[MAX_SPI_PORTS] =
{
  &GPIOPIN4OUT,
  &GPIOPIN28OUT,
#ifdef OLIMEX_STM32_P107
// For some reason, Olimex connected PB15 (SPI2 MOSI) to the UEXT NSS signal.
// This means we can't use both SPI3 on the UEXT connector and SPI2 on the
// expansion connector at the same time.
  &GPIOPIN31OUT,
#else
  &GPIOPIN41OUT,
#endif
};

#define SPIx_NSS		(*SPI_NSS_PIN[port-1])

/*****************************************************************************/

// Calculate the SPI clock prescaler for a given SPI clock rate.  Return an
// error if the requested SPI clock rate isn't possible.

static int SPI_Clock_Prescaler(uint32_t port,
                               uint32_t speed,
                               uint32_t *prescaler)
{
  RCC_ClocksTypeDef RCC_Clocks;
  uint32_t PCLK;

  errno_r = 0;

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
      errno_r = ENODEV;
      return __LINE__;
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

// Only the above SPI clock rates are possible.  Others are unrealizable.

  else
  {
    errno_r = EINVAL;
    return __LINE__;
  }

  return 0;
}

/*****************************************************************************/

static int SPI_Configure_Pins(uint32_t port)
{
  GPIO_InitTypeDef GPIO_config;

  errno_r = 0;

  switch (port)
  {
    case 1 :
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

      // Configure NSS pin

      gpiopin_configure(GPIOPIN4, GPIOPIN_OUTPUT);	// Use PA4 for NSS

      // Configure SCK pin

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_5;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA, &GPIO_config);

      // Configure MISO pin

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_6;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA, &GPIO_config);

      // Configure MOSI pin

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_7;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA, &GPIO_config);
      break;

    case 2 :
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

      // Configure NSS pin

      gpiopin_configure(GPIOPIN28, GPIOPIN_OUTPUT);	// Use PB12 for NSS

      // Configure SCK pin

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_13;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOB, &GPIO_config);

      // Configure MISO pin

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_14;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOB, &GPIO_config);

      // Configure MOSI pin

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_15;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOB, &GPIO_config);
      break;

    case 3 :
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

      // Configure NSS pin--Note we are using PC9 instead of PA4 or PA15!

#ifdef OLIMEX_STM32_P107
      gpiopin_configure(GPIOPIN31, GPIOPIN_OUTPUT);	// Use PB15 for NSS
#else
      gpiopin_configure(GPIOPIN41, GPIOPIN_OUTPUT);	// Use PC9 for NSS
#endif

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_9;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_Out_PP;
      GPIO_Init(GPIOC, &GPIO_config);

      // Configure SCK pin

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_10;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOC, &GPIO_config);

      // Configure MISO pin

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_11;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOC, &GPIO_config);

      // Configure MOSI pin

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_12;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOC, &GPIO_config);

      // Remap SPI3 pins; default pinout conflicts with JTAG

      GPIO_PinRemapConfig(GPIO_Remap_SPI3, ENABLE);
      break;

    default :
      errno_r = EINVAL;
      return __LINE__;
  }

  return 0;
}

/*****************************************************************************/

// Initialize SPI port for bidirection master mode

int spimaster_init(uint32_t port,
                   uint32_t clockmode,
                   uint32_t speed,
                   uint32_t bigendian)
{
  int status;
  uint32_t prescaler;
  SPI_InitTypeDef  SPI_InitStructure;

  errno_r = 0;

// Validate parameters

  if ((port < 1) && (port > MAX_SPI_PORTS))
  {
    errno_r = ENODEV;
    return __LINE__ - 3;
  }

  if (clockmode > 3)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if (bigendian > 1)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

// Get SPI clock prescaler

  if ((status = SPI_Clock_Prescaler(port, speed, &prescaler)))
    return status;

// Configure I/O pins

  if ((status = SPI_Configure_Pins(port)))
    return status;

// Deassert NSS

  SPIx_NSS = 1;

// Initialize the SPI port

  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = clockmode & 0x02;
  SPI_InitStructure.SPI_CPHA = clockmode & 0x01;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = prescaler;
  SPI_InitStructure.SPI_FirstBit = 
    bigendian ? SPI_FirstBit_MSB : SPI_FirstBit_LSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPIx, &SPI_InitStructure);

// Enable SPI port

  SPI_Cmd(SPIx, ENABLE);

  return 0;
}

/*****************************************************************************/

// Transmit command and/or receive result in bidirectional master mode

int spimaster_transfer(uint32_t port,
                       uint8_t *txbuf,
                       uint32_t txcount,
                       uint8_t *rxbuf,
                       uint32_t rxcount)
{
  errno_r = 0;

// Validate parameters

  if ((port < 1) && (port > MAX_SPI_PORTS))
  {
    errno_r = ENODEV;
    return __LINE__ - 3;
  }

  if ((txbuf == NULL) && (txcount != 0))
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if ((txcount == 0) && (txbuf != NULL))
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if ((rxbuf == NULL) && (rxcount != 0))
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if ((rxcount == 0) && (rxbuf != NULL))
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

// Assert NSS

  SPIx_NSS = 0;

// Transfer command data out

  while (txcount--)
  {
    while (!(SPIx->SR & SPI_I2S_FLAG_TXE));
    SPIx->DR = *txbuf++;
    while (!(SPIx->SR & SPI_I2S_FLAG_RXNE));
    (void) SPIx->DR;
  }

// Transfer response data in

  while (rxcount--)
  {
    while (!(SPIx->SR & SPI_I2S_FLAG_TXE));
    SPIx->DR = 0;
    while (!(SPIx->SR & SPI_I2S_FLAG_RXNE));
    *rxbuf++ = SPIx->DR;
  }

// Wait until the transfer is complete

  while (SPIx->SR & SPI_I2S_FLAG_BSY);

// Deassert NSS

  SPIx_NSS = 1;
  return 0;
}
