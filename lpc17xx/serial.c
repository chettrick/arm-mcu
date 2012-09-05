/******************************************************************************/
/*                                                                            */
/*          Simple serial port I/O routines for the LPC17xx ARM MCU           */
/*                                                                            */
/******************************************************************************/

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SERIAL_PORTS	4

static LPC_UART_TypeDef * const UARTS[MAX_SERIAL_PORTS] =
{
  (LPC_UART_TypeDef *) LPC_UART0,
  (LPC_UART_TypeDef *) LPC_UART1,
  (LPC_UART_TypeDef *) LPC_UART2,
  (LPC_UART_TypeDef *) LPC_UART3,
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

  errno_r = 0;

// Look up serial port number

  port = serial_name_to_port(name);
  if (port < 0) return port;

// Pass up port number, if requested

  if (subdevice != NULL)
    *subdevice = port;

// Extract baud rate from device name

  baudrate = lightweight_atoi(name+5);

  switch (port)
  {
    case 0 :
      LPC_SC->PCONP |= (1 << 3);		// Power on UART 0
      LPC_SC->PCLKSEL0 &= 0xFFFFFF3F;		// CCLK/4
      LPC_PINCON->PINSEL0 &= 0xFFFFFF0F;	// Enable UART 0 I/O pins
      LPC_PINCON->PINSEL0 |= 0x00000050;
      break;

    case 1 :
      LPC_SC->PCONP |= (1 << 4);		// Power on UART 1
      LPC_SC->PCLKSEL0 &= 0xFFFFFCFF;		// CCLK/4
      LPC_PINCON->PINSEL0 &= 0x3FFFFFFF;	// Enable UART 1 I/O pins
      LPC_PINCON->PINSEL0 |= 0x40000000;
      LPC_PINCON->PINSEL1 &= 0xFFFFFFFC;
      LPC_PINCON->PINSEL1 |= 0x00000001;
      break;

    case 2 :
      LPC_SC->PCONP |= (1 << 24);		// Power on UART 2
      LPC_SC->PCLKSEL1 &= 0xFFFCFFFF;		// CCLK/4
      LPC_PINCON->PINSEL0 &= 0xFF0FFFFF;	// Enable UART 2 I/O pins
      LPC_PINCON->PINSEL0 |= 0x00500000;
      break;

    case 3 :
      LPC_SC->PCONP |= (1 << 25);		// Power on UART 3
      LPC_SC->PCLKSEL1 &= 0xFFF3FFFF;		// CCLK/4
      LPC_PINCON->PINSEL0 &= 0xFFFFFFF0;	// Enable UART 3 I/O pins
      LPC_PINCON->PINSEL0 |= 0x0000000A;
      break;

    default :
      errno_r = ENODEV;
      return -1;
  }

// Configure baud rate

#include <lpc17xx_uart.h>

  UART_CFG_Type uartconfig;
  uartconfig.Baud_rate = baudrate;
  uartconfig.Parity = UART_PARITY_NONE;
  uartconfig.Databits = UART_DATABIT_8;
  uartconfig.Stopbits = UART_STOPBIT_1;
  UART_Init(UARTS[port], &uartconfig);

// Configure FIFO

  UART_FIFO_CFG_Type fifoconfig;
  UART_FIFOConfigStructInit(&fifoconfig);
  UART_FIFOConfig(UARTS[port], &fifoconfig);

// Enable the UART transmitter

  UART_TxCmd(UARTS[port], ENABLE);

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

/* Return TRUE if transmitter is ready to accept data */

int serial_txready(unsigned int port)
{
  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (UARTS[port]->LSR & 0x20)
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
    UARTS[port]->THR = *buf++;
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

  if (UARTS[port]->LSR & 0x01)
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
    *buf++ = UARTS[port]->RBR;
    return 1;
  }

  return 0;
}
