/******************************************************************************/
/*                                                                            */
/*                      Simple serial port I/O routines                       */
/*                                                                            */
/******************************************************************************/

// $Id$

/* Initialize serial port */

int serial_init(unsigned int port, unsigned long int baudrate);

/* Register serial port for standard I/O */

int serial_stdio(unsigned int port, unsigned long int baudrate);

/* Register a serial port device */

int serial_register(unsigned int port, unsigned long int baudrate);

/* Return TRUE if transmitter is ready to accept data */

int serial_txready(unsigned int port);

/* Write data to the serial port */

int serial_write(unsigned int port, char *buf, unsigned int count);

/* Return TRUE if receive data is available */

int serial_rxready(unsigned int port);

/* Read data from the serial port */

int serial_read(unsigned int port, char *buf, unsigned int count);
