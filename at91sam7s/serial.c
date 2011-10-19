/******************************************************************************/
/*                                                                            */
/*     Simple serial console I/O routines for the Atmel AT91SAM7S ARM MCU     */
/*                                                                            */
/******************************************************************************/

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SERIAL_PORTS	2

/* Define relocatable UART register definitions */

static const unsigned long int UARTS[MAX_SERIAL_PORTS] =
{
  (unsigned long int) AT91C_BASE_US0,
  (unsigned long int) AT91C_BASE_US1
};

#define US_CR	(*(volatile unsigned long int *)(UARTS[port] + 0x00))
#define US_MR	(*(volatile unsigned long int *)(UARTS[port] + 0x04))
#define US_CSR	(*(volatile unsigned long int *)(UARTS[port] + 0x14))
#define US_RHR	(*(volatile unsigned long int *)(UARTS[port] + 0x18))
#define US_THR	(*(volatile unsigned long int *)(UARTS[port] + 0x1C))
#define US_BRGR	(*(volatile unsigned long int *)(UARTS[port] + 0x20))

/* Initialize serial port */

int serial_open(char *name, unsigned int *subdevice)
{
  unsigned int port;
  unsigned int baudrate;

  errno_r = 0;

// Map serial port device name to port number

  if (!strncasecmp(name, "com1:", 5))
    port = 0;
  else if (!strncasecmp(name, "com2:", 5))
    port = 1;
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

// Configure peripheral clock and I/O pins for UART

  switch (port)
  {
    case 0 :
      *AT91C_PMC_PCER = 0x00000040;
      *AT91C_PIOA_ASR = 0x00000060;
      *AT91C_PIOA_PDR = 0x00000060;
      break;

    case 1 :
      *AT91C_PMC_PCER = 0x00000080;
      *AT91C_PIOA_ASR = 0x00600000;
      *AT91C_PIOA_PDR = 0x00600000;
      break;

    default :
      errno_r = ENODEV;
      return -1;
  }

// Configure UART

  US_CR = 0x00000050;
  US_MR = 0x000008C0;
  US_BRGR = CPUFREQ/16/baudrate;

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

  if (US_CSR & AT91C_US_TXRDY)
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
    US_THR = *buf++;
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

  if (US_CSR & AT91C_US_RXRDY)
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
    *buf++ = US_RHR;
    return 1;
  }

  return 0;
}
