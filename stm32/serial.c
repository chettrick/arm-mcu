/******************************************************************************/
/*                                                                            */
/*      Simple serial port I/O routines for the STM32 Cortex-M3 ARM MCU       */
/*                                                                            */
/******************************************************************************/

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SERIAL_PORTS	3

static USART_TypeDef * const UARTS[MAX_SERIAL_PORTS] =
{
  USART1,
  USART2,
  USART3,
};

/* Initialize serial port */

int serial_init(char *name, unsigned int *subdevice)
{
  unsigned int port;
  unsigned int baudrate;
  USART_InitTypeDef USART_config;
  GPIO_InitTypeDef GPIO_config;

  errno_r = 0;

// Map serial port device name to port number

  if (!strncasecmp(name, "com1:", 5))
    port = 0;
  else if (!strncasecmp(name, "com2:", 5))
    port = 1;
  else if (!strncasecmp(name, "com3:", 5))
    port = 2;
  else
  {
    errno_r = ENODEV;
    return -1;
  }

// Pass up port number, if requested

  if (subdevice != NULL)
    *subdevice = port;

// Extract baud rate from device name

  baudrate = atoi(name+5);

// Turn on USART

  switch (port)
  {
    case 0 :
#ifdef OLIMEX_STM32_P107
// Turn on peripheral clocks

      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

// Configure TX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_6;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOB, &GPIO_config);

// Configure RX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_7;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      GPIO_Init(GPIOB, &GPIO_config);

// Remap USART1 pins

      GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
#else
// Turn on peripheral clocks

      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

// Configure TX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_9;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA, &GPIO_config);

// Configure RX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_10;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      GPIO_Init(GPIOA, &GPIO_config);
#endif
      break;
 
    case 1 :
#ifdef OLIMEX_STM32_P107
// Turn on peripheral clocks

      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

// Configure TX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_5;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOD, &GPIO_config);

// Configure RX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_6;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      GPIO_Init(GPIOD, &GPIO_config);

// Remap USART2 pins

      GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
#else
// Turn on peripheral clocks

      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

// Configure TX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_2;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA, &GPIO_config);

// Configure RX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_3;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      GPIO_Init(GPIOA, &GPIO_config);
#endif
      break;
 
    case 2 :
#ifdef OLIMEX_STM32_P107
// Turn on peripheral clocks

      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

// Configure TX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_8;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOD, &GPIO_config);

// Configure RX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_9;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      GPIO_Init(GPIOD, &GPIO_config);

// Remap USART3 pins

      GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);
#else
// Turn on peripheral clocks

      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

// Configure TX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_10;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOB, &GPIO_config);

// Configure RX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_11;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      GPIO_Init(GPIOB, &GPIO_config);
#endif
      break;

    default :
      errno_r = ENODEV;
      return -1;
  }

// Configure USART

  USART_StructInit(&USART_config);
  USART_config.USART_BaudRate = baudrate;
  USART_config.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(UARTS[port], &USART_config);

// Enable USART

  USART_Cmd(UARTS[port], ENABLE);

  return 0;
}

/* Register serial port for standard I/O */

int serial_stdio(char *name)
{
  unsigned int subdevice;

  if (serial_init(name, &subdevice))
    return -1;

  // Nuke existing stdin, stdout, stderr

  device_unregister(0);
  device_unregister(1);
  device_unregister(2);

  // Register new stdin, stdout, stderr

  device_register_char_fd(0, subdevice, NULL, serial_read, NULL, serial_rxready);
  device_register_char_fd(1, subdevice, serial_write, NULL, serial_txready, NULL);
  device_register_char_fd(2, subdevice, serial_write, NULL, serial_txready, NULL);

  return 0;
}

/* Register a serial port device */

int serial_register(char *name)
{
  return device_register_char(name, serial_init, serial_write, serial_read, serial_txready, serial_rxready);
}

/* Return TRUE if transmitter is ready to accept data */

int serial_txready(unsigned int port)
{
  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (UARTS[port]->SR & USART_FLAG_TXE)
    return 1;
  else
    return 0;
}

/* Send a buffer to the serial port */

int serial_write(unsigned int port, char *buf, unsigned int count)
{
  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (serial_txready(port))
  {
    UARTS[port]->DR = *buf++;
    return 1;
  }

  return 0;
}

/* Return TRUE if receive data is available */

int serial_rxready(unsigned int port)
{
  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (UARTS[port]->SR & USART_FLAG_RXNE)
    return 1;
  else
    return 0;
}

/* Read buffer from the serial port */

int serial_read(unsigned int port, char *buf, unsigned int count)
{
  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (serial_rxready(port))
  {
    *buf++ = UARTS[port]->DR;

    return 1;
  }

  return 0;
}
