/******************************************************************************/
/*                                                                            */
/*     Simple serial port I/O routines for the STM32F4 Cortex-M4 ARM MCU      */
/*                                                                            */
/******************************************************************************/

// $Id: serial.c 3206 2011-10-19 13:12:40Z svn $

static const char revision[] = "$Id: serial.c 3206 2011-10-19 13:12:40Z svn $";

#include <cpu.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SERIAL_PORTS	6

static USART_TypeDef * const UARTS[MAX_SERIAL_PORTS] =
{
  USART1,
  USART2,
  USART3,
  UART4,
  UART5,
  USART6,
};

/* Initialize serial port */

int serial_open(char *name, unsigned int *subdevice)
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
  else if (!strncasecmp(name, "com4:", 5))
    port = 3;
  else if (!strncasecmp(name, "com5:", 5))
    port = 4;
  else if (!strncasecmp(name, "com6:", 5))
    port = 5;
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
    case 0 : // USART1

// Turn on peripheral clocks

      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

// Configure TX pin on PA9

      GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_9;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_OType = GPIO_OType_PP;
      GPIO_Init(GPIOA, &GPIO_config);

// Configure RX pin PA10

      GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_10;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF;
      GPIO_config.GPIO_PuPd = GPIO_PuPd_UP;
      GPIO_Init(GPIOA, &GPIO_config);
      break;

    case 1 : // USART2

// Turn on peripheral clocks

      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

// Configure TX pin on PA2

      GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_2;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_OType = GPIO_OType_PP;
      GPIO_Init(GPIOA, &GPIO_config);

// Configure RX pin on PA3

      GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_3;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF;
      GPIO_config.GPIO_PuPd = GPIO_PuPd_UP;
      GPIO_Init(GPIOA, &GPIO_config);
      break;

    case 2 : // USART3

// Turn on peripheral clocks

      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

// Configure TX pin on PB10

      GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_10;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_OType = GPIO_OType_PP;
      GPIO_Init(GPIOB, &GPIO_config);

// Configure RX pin on PB11

      GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_11;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF;
      GPIO_config.GPIO_PuPd = GPIO_PuPd_UP;
      GPIO_Init(GPIOB, &GPIO_config);
      break;

    case 3 : // UART4

// Turn on peripheral clocks

      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

// Configure TX pin on PA0

      GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_0;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_OType = GPIO_OType_PP;
      GPIO_Init(GPIOA, &GPIO_config);

// Configure RX pin on PA1

      GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_1;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF;
      GPIO_config.GPIO_PuPd = GPIO_PuPd_UP;
      GPIO_Init(GPIOA, &GPIO_config);
      break;

    case 4 : // UART5

// Turn on peripheral clocks

      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);

// Configure TX pin on PC12

      GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_12;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_OType = GPIO_OType_PP;
      GPIO_Init(GPIOC, &GPIO_config);

// Configure RX pin on PD2

      GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_2;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF;
      GPIO_config.GPIO_PuPd = GPIO_PuPd_UP;
      GPIO_Init(GPIOD, &GPIO_config);
      break;

    case 5 : //  USART6

// Turn on peripheral clocks

      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

// Configure TX pin on PC6

      GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_6;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_OType = GPIO_OType_PP;
      GPIO_Init(GPIOC, &GPIO_config);

// Configure RX pin on PC7

      GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

      GPIO_StructInit(&GPIO_config);
      GPIO_config.GPIO_Pin = GPIO_Pin_7;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF;
      GPIO_config.GPIO_PuPd = GPIO_PuPd_UP;
      GPIO_Init(GPIOC, &GPIO_config);
      break;

    default :
      errno_r = ENODEV;
      return -1;
  }

// Configure USART

  USART_StructInit(&USART_config);
  USART_config.USART_BaudRate = baudrate;
  USART_Init(UARTS[port], &USART_config);

// Enable USART

  USART_Cmd(UARTS[port], ENABLE);

  return 0;
}

/* Register serial port for standard I/O */

int serial_stdio(char *name)
{
  unsigned int subdevice;

  if (serial_open(name, &subdevice))
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
  return device_register_char(name, serial_open, NULL, serial_write, serial_read, serial_txready, serial_rxready);
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
