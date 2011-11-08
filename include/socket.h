/* TCP/IP socket API (Application Programming Interface.  These functions are */
/* implemented in the various network device drivers and server to bind those */
/* drivers to the ARM device infrastructure.  When the following functions    */
/* implemented and registered to a file discriptor using the                  */
/* device_register_char() function, the TCP/IP socket can then be completely  */
/* manipulated via the formal file I/O functions such as open(), read() and   */
/* like.                                                                      */

// $Id$

extern int socket_open(char *name, unsigned int *subdevice);

extern int socket_close(unsigned int subdevice);

extern int socket_write(unsigned int subdevice, char *buf, unsigned int count);

extern int socket_read(unsigned int subdevice, char *buf, unsigned int count);

extern int socket_write_ready(unsigned int subdevice);

extern int socket_read_ready(unsigned int subdevice);
