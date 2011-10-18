/******************************************************************************/
/*                                                                            */
/*          Simple serial port I/O routines for the EFM32 ARM MCU             */
/*                                                                            */
/******************************************************************************/

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SERIAL_PORTS	1

static USART_TypeDef * const UARTS[MAX_SERIAL_PORTS] =
{
  UART0,
};

/* Initialize serial port */

int serial_init(char *name, unsigned int *subdevice)
{
  unsigned int port;
  unsigned int baudrate;
  USART_InitAsync_TypeDef usartInit;

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

  switch (port)
  {
    case 0 :
// Enable peripheral clocks

      CMU_ClockEnable(cmuClock_GPIO, true);
      CMU_ClockEnable(cmuClock_UART0, true);

// Configure I/O pins

      GPIO_PinModeSet(gpioPortE, 0, gpioModePushPull, 1);
      GPIO_PinModeSet(gpioPortE, 1, gpioModeInput, 1);

#ifdef EFM32_G8XX_STK
// Clear BC_EN to disconnect UART0 from board controller

      GPIO_PinModeSet(gpioPortD, 13, gpioModePushPull, 1);
      GPIO_PinOutClear(gpioPortD, 13);

// Route UART pins to PE0 and PE1

      UARTS[port]->ROUTE = USART_ROUTE_RXPEN|USART_ROUTE_TXPEN|USART_ROUTE_LOCATION_LOC1;
#endif
      break;

    default :
      errno_r = ENODEV;
      return -1;
  }

// Configure the serial port

  usartInit.enable = usartEnable;
  usartInit.refFreq = 0;
  usartInit.baudrate = baudrate;
  usartInit.oversampling = usartOVS16;
  usartInit.databits = usartDatabits8;
  usartInit.parity = usartNoParity;
  usartInit.stopbits = usartStopbits1;

  USART_InitAsync(UARTS[port], &usartInit);

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

  if (UARTS[port]->STATUS & USART_STATUS_TXBL)
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
    UARTS[port]->TXDATA = *buf++;
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

  if (UARTS[port]->STATUS & USART_STATUS_RXDATAV)
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
    *buf++ = UARTS[port]->RXDATA;
    return 1;
  }

  return 0;
}
