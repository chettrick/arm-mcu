/******************************************************************************/
/*                                                                            */
/*          Simple serial port I/O routines for the EFM32 ARM MCU             */
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
  UART0,
};

/* Initialize serial console */

int serial_init(unsigned port, unsigned long int baudrate)
{
  USART_InitAsync_TypeDef usartInit;

  errno = 0;

  switch (port)
  {
    case 0 :
// Enable peripheral clocks

      CMU_ClockEnable(cmuClock_HF, true);
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
      errno = ENODEV;
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

int serial_stdio(unsigned port, unsigned long int baudrate)
{
  int status;

  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
    return -1;
  }

  status = serial_init(port, baudrate);
  if (status) return status;

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

  if (port+1 > MAX_SERIAL_PORTS)
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

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
    return -1;
  }

  if (UARTS[port]->STATUS & USART_STATUS_TXBL)
    return 1;
  else
    return 0;
}

/* Send a buffer to the serial port */

int serial_write(unsigned port, char *buf, unsigned int count)
{
  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
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

int serial_rxready(unsigned port)
{
  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
    return -1;
  }

  if (UARTS[port]->STATUS & USART_STATUS_RXDATAV)
    return 1;
  else
    return 0;
}

/* Read buffer from the serial port */

int serial_read(unsigned port, char *buf, unsigned int count)
{
  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
    return -1;
  }

  if (serial_rxready(port))
  {
    *buf++ = UARTS[port]->RXDATA;
    return 1;
  }

  return 0;
}
