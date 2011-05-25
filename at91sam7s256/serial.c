/******************************************************************************/
/*                                                                            */
/*   Simple serial console I/O routines for the Atmel AT91SAM7S256 ARM MCU    */
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

/* Define relocatable UART register definitions */

static const unsigned long int UARTS[MAX_SERIAL_PORTS] =
{
  (unsigned long int) AT91C_BASE_US0,
  (unsigned long int) AT91C_BASE_US1
};

#define US_CR	(*(volatile unsigned long *)(UARTS[port] + 0x00))
#define US_MR	(*(volatile unsigned long *)(UARTS[port] + 0x04))
#define US_CSR	(*(volatile unsigned long *)(UARTS[port] + 0x14))
#define US_RHR	(*(volatile unsigned long *)(UARTS[port] + 0x18))
#define US_THR	(*(volatile unsigned long *)(UARTS[port] + 0x1C))
#define US_BRGR	(*(volatile unsigned long *)(UARTS[port] + 0x20))

/* Initialize serial console */

int serial_init(unsigned port, unsigned long int baudrate)
{
  errno = 0;

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

  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
    return -1;
  }

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
    return 0;
  }

  return US_CSR & AT91C_US_TXRDY;
}

/* Send a buffer to the serial port */

int serial_write(unsigned port, char *buf, unsigned int count)
{
  int n;

  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
    return -1;
  }

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
  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
    return 0;
  }

  return US_CSR & AT91C_US_RXRDY;
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
    *buf = US_RHR;
    return 1;
  }
  else
    return 0;
}
