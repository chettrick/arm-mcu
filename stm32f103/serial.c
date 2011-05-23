/******************************************************************************/
/*                                                                            */
/*    Simple serial port I/O routines for the STM32F103 Cortex-M3 ARM MCU     */
/*                                                                            */
/******************************************************************************/

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#undef errno
extern int errno;

static USART_TypeDef * const UARTS[MAX_SERIAL_PORTS] =
{
  USART1,
  USART2,
  USART3,
};

/* Initialize serial console */

int serial_init(unsigned port, unsigned long int baudrate)
{
  USART_InitTypeDef USART_config;
  GPIO_InitTypeDef GPIO_config;

  errno = 0;

  if ((port < 1) || (port > MAX_SERIAL_PORTS))
  {
    errno = ENODEV;
    return -1;
  }

// Turn on USART

  switch (port)
  {
    case 1 :

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
 
    case 2 :

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
 
    case 3 :

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
      break;

    default :
      errno = ENODEV;
      return -1;
  }

// Configure USART

  USART_StructInit(&USART_config);
  USART_config.USART_BaudRate = baudrate;
  USART_Init(UARTS[port-1], &USART_config);

// Enable USART

  USART_Cmd(UARTS[port-1], ENABLE);

  return 0;
}

/* Register serial port for standard I/O */

int serial_stdio(unsigned port, unsigned long int baudrate)
{
  errno = 0;

  if ((port < 1) || (port > MAX_SERIAL_PORTS))
  {
    errno = ENODEV;
    return -1;
  }

  serial_init(port, baudrate);

  device_register_char_fd(NULL, 0, port, (void *) baudrate, (device_init_t) serial_init, NULL, serial_read, NULL, serial_rxready);
  device_register_char_fd(NULL, 1, port, (void *) baudrate, (device_init_t) serial_init, serial_write, NULL, serial_txready, NULL);
  device_register_char_fd(NULL, 2, port, (void *) baudrate, (device_init_t) serial_init, serial_write, NULL, serial_txready, NULL);

  return 0;
}

/* Register a serial port device */

int serial_register(unsigned port, unsigned long int baudrate)
{
  int status;
  char name[DEVICE_NAME_SIZE];

  errno = 0;

  if ((port < 1) || (port > MAX_SERIAL_PORTS))
  {
    errno = ENODEV;
    return -1;
  }

  status = serial_init(port, baudrate);
  if (status) return status;

  memset(name, 0, sizeof(name));
  siprintf(name, "com%d", port);

  device_register_char(name, port, (void *) baudrate,
   (device_init_t) serial_init, serial_write, serial_read, serial_txready, serial_rxready);

  return 0;
}

/* Return TRUE if transmitter is ready to accept data */

int serial_txready(unsigned port)
{
  errno = 0;

  if ((port < 1) || (port > MAX_SERIAL_PORTS))
  {
    errno = ENODEV;
    return 0;
  }

  return UARTS[port-1]->SR & USART_FLAG_TXE;
}

/* Send a buffer to the serial port */

int serial_write(unsigned port, char *buf, unsigned int count)
{
  int n;

  errno = 0;

  if ((port < 1) || (port > MAX_SERIAL_PORTS))
  {
    errno = ENODEV;
    return -1;
  }

  for (n = 0; n < count; n++)
  {
    while (!serial_txready(port));
    UARTS[port-1]->DR = *buf++;
  }

  return count;
}

/* Return TRUE if receive data is available */

int serial_rxready(unsigned port)
{
  errno = 0;

  if ((port < 1) || (port > MAX_SERIAL_PORTS))
  {
    errno = ENODEV;
    return 0;
  }

  return UARTS[port-1]->SR & USART_FLAG_RXNE;
}

/* Read buffer from the serial port */

int serial_read(unsigned port, char *buf, unsigned int count)
{
  errno = 0;

  if ((port < 1) || (port > MAX_SERIAL_PORTS))
  {
    errno = ENODEV;
    return -1;
  }

  if (serial_rxready(port))
  {
    *buf = UARTS[port-1]->DR;

    return 1;
  }
  else
    return 0;
}
