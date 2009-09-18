/******************************************************************************/
/*                                                                            */
/*   Simple serial console I/O routines for the Atmel AT91SAM7S256 ARM MCU    */
/*                                                                            */
/******************************************************************************/

// $Id$

#include <cpu.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#undef errno
extern int errno;

/* Define relocatable UART register definitions */

static unsigned long int UARTBASE = (unsigned long int) AT91C_BASE_US0;

#define US_CR	(*(volatile unsigned long *)(UARTBASE + 0x00))
#define US_MR	(*(volatile unsigned long *)(UARTBASE + 0x04))
#define US_CSR	(*(volatile unsigned long *)(UARTBASE + 0x14))
#define US_RHR	(*(volatile unsigned long *)(UARTBASE + 0x18))
#define US_THR	(*(volatile unsigned long *)(UARTBASE + 0x1C))
#define US_BRGR	(*(volatile unsigned long *)(UARTBASE + 0x20))

/* Initialize serial console */

int serial_init(unsigned port, unsigned long int baudrate)
{
  errno = 0;

// Configure peripheral clock and I/O pins for UART

  switch (port)
  {
    case 0 :
      UARTBASE = (unsigned long int) AT91C_BASE_US0;
      *AT91C_PMC_PCER = 0x00000040;
      *AT91C_PIOA_ASR = 0x00000060;
      *AT91C_PIOA_PDR = 0x00000060;
      break;

    case 1 :
      UARTBASE = (unsigned long int) AT91C_BASE_US1;
      *AT91C_PMC_PCER = 0x00000080;
      *AT91C_PIOA_ASR = 0x00600000;
      *AT91C_PIOA_PDR = 0x00600000;
      break;

    default :
      errno = ENODEV;
      return -1;
  }

// Configure UART

  US_CR = 0x00000050;
  US_MR = 0x000008C0;
  US_BRGR = CPUFREQ/16/baudrate;

  return 0;
}

/* Register serial port for standard I/O */

int serial_stdio(unsigned port, unsigned long int baudrate)
{
  serial_init(port, baudrate);

  device_unregister("stdin");
  device_unregister("stdout");
  device_unregister("stderr");

  device_register_fd("stdin", DEVICE_TYPE_CHAR, 0, port, (void *) baudrate,
    (device_init_t) serial_init, serial_write, serial_read, serial_txready, serial_rxready);

  device_register_fd("stdout", DEVICE_TYPE_CHAR, 1, port, (void *) baudrate,
    (device_init_t) serial_init, serial_write, serial_read, serial_txready, serial_rxready);

  device_register_fd("stderr", DEVICE_TYPE_CHAR, 2, port, (void *) baudrate,
    (device_init_t) serial_init, serial_write, serial_read, serial_txready, serial_rxready);

  return 0;
}

/* Return TRUE if transmitter is ready to accept data */

int serial_txready(unsigned port)
{
  return US_CSR & AT91C_US_TXRDY;
}

/* Send a buffer to the serial port */

int serial_write(unsigned port, char *buf, unsigned int count)
{
  int n;

  for (n = 0; n < count; n++)
  {
    while (!serial_txready(port));
    US_THR = *buf++;
  }

  return count;
}

/* Return TRUE if receive data is available */

int serial_rxready(unsigned port)
{
  return US_CSR & AT91C_US_RXRDY;
}

/* Read buffer from the serial port */

int serial_read(unsigned port, char *buf, unsigned int count)
{
  if (serial_rxready(port))
  {
    *buf = US_RHR;
    return 1;
  }
  else
    return 0;
}
