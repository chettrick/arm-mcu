/******************************************************************************/
/*                                                                            */
/*                      Simple serial port I/O routines                       */
/*                                                                            */
/******************************************************************************/

// $Id$

#ifndef _SERIAL_H
#define _SERIAL_H

#include <_ansi.h>

_BEGIN_STD_C

/* Initialize serial port */

int serial_open(char *name, unsigned int *subdevice);

/* Register serial port for standard I/O */

int serial_stdio(char *name);

/* Register a serial port device */

int serial_register(char *name);

/* Return TRUE if transmitter is ready to accept data */

int serial_txready(unsigned int port);

/* Write data to the serial port */

int serial_write(unsigned int port, char *buf, unsigned int count);

/* Return TRUE if receive data is available */

int serial_rxready(unsigned int port);

/* Read data from the serial port */

int serial_read(unsigned int port, char *buf, unsigned int count);

_END_STD_C
#endif
