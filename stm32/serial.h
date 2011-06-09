/******************************************************************************/
/*                                                                            */
/*      Simple serial port I/O routines for the STM32 Cortex-M3 ARM MCU       */
/*                                                                            */
/******************************************************************************/

// $Id$

#define MAX_SERIAL_PORTS	3

/* Initialize serial port */

int serial_init(unsigned port, unsigned long int baudrate);

/* Register serial port for standard I/O */

int serial_stdio(unsigned port, unsigned long int baudrate);

/* Register a serial port device */

int serial_register(unsigned port, unsigned long int baudrate);

/* Return TRUE if transmitter is ready to accept data */

int serial_txready(unsigned port);

/* Write data to the serial port */

int serial_write(unsigned port, char *buf, unsigned int count);

/* Return TRUE if receive data is available */

int serial_rxready(unsigned port);

/* Read data from the serial port */

int serial_read(unsigned port, char *buf, unsigned int count);
