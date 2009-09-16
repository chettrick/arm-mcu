/******************************************************************************/
/*                                                                            */
/*    Simple serial port I/O routines for the STM32F103 Cortex-M3 ARM MCU     */
/*                                                                            */
/******************************************************************************/

// $Id$

#include <cpu.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#undef errno
extern int errno;

static USART_TypeDef *UART = (USART_TypeDef *) USART1_BASE;

/* Initialize serial console */

int serial_init(unsigned port, unsigned long int baudrate)
{
  USART_InitTypeDef USART_config;
  GPIO_InitTypeDef GPIO_config;

  errno = 0;

// Turn on USART

  switch (port)
  {
    case 0 :
      UART = (USART_TypeDef *) USART1_BASE;

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
      break;
 
    case 1 :
      UART = (USART_TypeDef *) USART2_BASE;

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
      break;
 
    case 2 :
      UART = (USART_TypeDef *) USART3_BASE;

// Turn on peripheral clocks

      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

// Configure TX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_10;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA, &GPIO_config);

// Configure RX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_11;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      GPIO_Init(GPIOB, &GPIO_config);
      break;

    default :
      errno = ENODEV;
      return -1;
  }

// Configure USART

  USART_StructInit(&USART_config);
  USART_config.USART_BaudRate = baudrate;
  USART_Init(UART, &USART_config);
  USART_Cmd(UART, ENABLE);

  return 0;
}

/* Register serial port for standard I/O */

int serial_stdio(unsigned port, unsigned long int baudrate)
{
  serial_init(port, baudrate);

  device_unregister("stdin");
  device_unregister("stdout");
  device_unregister("stderr");

  device_register_fd("stdin",  0, port, (void *) baudrate, (device_init_t) serial_init,
                     serial_write, serial_read, serial_txready, serial_rxready);

  device_register_fd("stdout", 1, port, (void *) baudrate, (device_init_t) serial_init,
                     serial_write, serial_read, serial_txready, serial_rxready);

  device_register_fd("stderr", 2, port, (void *) baudrate, (device_init_t) serial_init,
                     serial_write, serial_read, serial_txready, serial_rxready);

  return 0;
}

/* Return TRUE if transmitter is ready to accept data */

int serial_txready(unsigned port)
{
  return UART->SR & USART_FLAG_RXNE;
}

/* Send 1 byte to the serial port */

static void serial_putch(unsigned port, char c)
{
  while (!serial_txready(port));
  UART->DR = c;
}

/* Send a buffer to the serial port */

int serial_write(unsigned port, char *buf, unsigned int count)
{
  int n;

  for (n = 0; n < count; n++)
    serial_putch(port, *buf++);

  return count;
}

/* Return TRUE if receive data is available */

int serial_rxready(unsigned port)
{
  return UART->SR & USART_FLAG_RXNE;
}

/* Read buffer from the serial port */

int serial_read(unsigned port, char *buf, unsigned int count)
{
  if (serial_rxready(port))
  {
    *buf = UART->DR;
    return 1;
  }
  else
    return 0;
}
