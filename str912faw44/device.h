/******************************************************************************/
/*                                                                            */
/*        Simple serial port I/O routines for the STR912FAW44 ARM MCU         */
/*                                                                            */
/******************************************************************************/

// $Id: device.h,v 1.1 2008-08-14 20:08:18 cvs Exp $

#include <unistd.h>

#define MAX_DEVICES	16

typedef int (*device_init_t)		(unsigned subdevice, void *settings);
typedef int (*device_write_t)		(unsigned subdevice, char *buf, size_t count);
typedef int (*device_read_t)		(unsigned subdevice, char *buf, size_t count);
typedef int (*device_write_ready_t)	(unsigned subdevice);
typedef int (*device_read_ready_t)	(unsigned subdevice);

typedef struct
{
  char name[MAXPATHLEN];
  unsigned subdevice;
  void *settings;
  device_init_t init;
  device_write_t write;
  device_read_t read;
  device_write_ready_t write_ready;
  device_read_ready_t read_ready;
} device_t;

extern device_t device_table[MAX_DEVICES];

// Device registration functions

int device_register(char *name, unsigned subdevice, void *settings,
                    device_init_t init, device_write_t write, device_read_t read,
                    device_write_ready_t write_ready, device_read_ready_t read_ready);

int device_register_fd(char *name, int fd, unsigned subdevice, void *settings,
                       device_init_t init, device_write_t write, device_read_t read,
                       device_write_ready_t write_ready, device_read_ready_t read_ready);

int device_unregister(char *name);
int device_lookup(char *name);

// Non-buffered I/O helper functions

int device_ready_write(int fd);
int device_ready_read(int fd);
int device_putc(int fd, char c);
int device_puts(int fd, char *s);
int device_getc(int fd);
int device_gets(int fd, char *s, size_t size);

// Convenience macros, vaguely inspired by Turbo C and Turbo Pascal

#define putch(c)	(device_putc(fileno(stdout), c))
#define cputs(s)	(device_puts(fileno(stdout), s))
#define keypressed(...)	(device_ready_read(fileno(stdout)))
#define getch(...)	(device_getc(fileno(stdin)))
#define cgets(s, size)	(device_gets(fileno(stdin), s, size))
