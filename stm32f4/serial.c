/******************************************************************************/
/*                                                                            */
/*     Simple serial port I/O routines for the STM32F4 Cortex-M4 ARM MCU      */
/*                                                                            */
/******************************************************************************/

// $Id: serial.c 3206 2011-10-19 13:12:40Z svn $

// Copyright (C)2013, Philip Munts, President, Munts AM Corp.
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

static const char revision[] = "$Id: serial.c 3206 2011-10-19 13:12:40Z svn $";

#include <cpu.h>
#include <errno.h>
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

/* Lightweight alternative to newlib atoi() */

static int lightweight_atoi(const char *s)
{
  int x = 0;

  while (*s)
  {
    char c = *s++;

    if ((c >= '0') && (c <= '9'))
      x = x*10 + c - '0';
    else
      break;
  }

  return x;
}

/* Map serial port device name to port number */

int serial_name_to_port(char *name)
{
  errno_r = 0;

  if (!strncasecmp(name, "com1:", 5))
    return 0;
  else if (!strncasecmp(name, "com2:", 5))
    return 1;
  else if (!strncasecmp(name, "com3:", 5))
    return 2;
  else if (!strncasecmp(name, "com4:", 5))
    return 3;
  else if (!strncasecmp(name, "com5:", 5))
    return 4;
  else if (!strncasecmp(name, "com6:", 5))
    return 5;
  else
  {
    errno_r = ENODEV;
    return -1;
  }
}

/* Initialize serial port */

int serial_open(char *name, unsigned int *subdevice)
{
  unsigned int port;
  unsigned int baudrate;
  USART_InitTypeDef USART_config;
  GPIO_InitTypeDef GPIO_config;

  errno_r = 0;

// Look up serial port number

  port = serial_name_to_port(name);
  if (port < 0) return port;

// Pass up port number, if requested

  if (subdevice != NULL)
    *subdevice = port;

// Extract baud rate from device name

  baudrate = lightweight_atoi(name+5);

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
  unsigned int port;

// Look up serial port number

  port = serial_name_to_port(name);
  if (port < 0) return port;

// Register the serial port driver

  return device_register_char(name, port, serial_open, NULL, serial_write, serial_read, serial_txready, serial_rxready);
}

/* Return true if transmitter is ready to accept data */

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

/* Return true if receive data is available */

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
