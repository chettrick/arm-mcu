/******************************************************************************/
/*                                                                            */
/*        Simple serial port I/O routines for the STR912FAW44 ARM MCU         */
/*                                                                            */
/******************************************************************************/

// $Id: device.c,v 1.2 2008-08-15 15:54:20 cvs Exp $

#include <cpu.h>
#include <string.h>
#include <errno.h>
#undef errno
extern int errno;

device_t device_table[MAX_DEVICES];

/* Register a device to the next available file descriptor */

int device_register(char *name, unsigned subdevice, void *settings,
                    device_init_t init, device_write_t write, device_read_t read,
                    device_write_ready_t write_ready, device_read_ready_t read_ready)
{
  int d;

  if (device_lookup(name) >= 0)
  {
    errno = EEXIST;
    return -1;
  }
  
  for (d = 3; d < MAX_DEVICES; d++)
    if (device_table[d].name[0] == 0)
    {
      strlcpy(device_table[d].name, name, sizeof(device_table[d].name));
      device_table[d].subdevice = subdevice;
      device_table[d].settings = settings;
      device_table[d].init = init;
      device_table[d].write = write;
      device_table[d].read = read;
      device_table[d].write_ready = write_ready;
      device_table[d].read_ready = read_ready;
      return 0;
    }

  errno = ENOMEM;
  return -1;
}

/* Register a device to a specific file descripter */

int device_register_fd(char *name, int fd, unsigned subdevice, void *settings,
                       device_init_t init, device_write_t write, device_read_t read,
                       device_write_ready_t write_ready, device_read_ready_t read_ready)
{
  if (device_lookup(name) >= 0)
  {
    errno = EEXIST;
    return -1;
  }

  if (fd >= MAX_DEVICES)
  {
    errno = EINVAL;
    return -1;
  }

  strlcpy(device_table[fd].name, name, MAXPATHLEN);
  device_table[fd].subdevice = subdevice;
  device_table[fd].settings = settings;
  device_table[fd].init = init;
  device_table[fd].write = write;
  device_table[fd].read = read;
  device_table[fd].write_ready = write_ready;
  device_table[fd].read_ready = read_ready;

  return 0;
}

/* Unregister a device */

int device_unregister(char *name)
{
  int d;

  d = device_lookup(name);
  if (d < 0) return d;

  memset(&device_table[d], 0, sizeof(device_t));
  return 0;
}

/* Lookup a device */

int device_lookup(char *name)
{
  int d;

  for (d = 0; d < MAX_DEVICES; d++)
    if (!strcasecmp(device_table[d].name, name))
      return d;

  errno = ENODEV;
  return -1;
}

/* Return TRUE if the device is ready to accept transmit data */

int device_ready_write(int fd)
{
  if (device_table[fd].name[0] == 0)
  {
    errno = ENODEV;
    return -1;
  }

  if (device_table[fd].write_ready == NULL)
  {
    errno = EIO;
    return -1;
  }

  return device_table[fd].write_ready(device_table[fd].subdevice);
}

/* Return TRUE if the device has received data available */

int device_ready_read(int fd)
{
  if (device_table[fd].name[0] == 0)
  {
    errno = ENODEV;
    return -1;
  }

  if (device_table[fd].read_ready == NULL)
  {
    errno = EIO;
    return -1;
  }

  return device_table[fd].read_ready(device_table[fd].subdevice);
}

/* Write a single character to a device */

int device_putc(int fd, char c)
{
  return _write(fd, &c, 1);
}

/* Write a string to a device */

int device_puts(int fd, char *s)
{
  return _write(fd, s, strlen(s));
}

/* Read a single character from a device */

int device_getc(int fd)
{
  int len;
  char c;

  if (device_table[fd].name[0] == 0)
  {
    errno = ENODEV;
    return -1;
  }

  if (device_table[fd].read == NULL)
  {
    errno = EIO;
    return -1;
  }

  while ((len = device_table[fd].read(device_table[fd].subdevice, &c, 1)) == 0);

  if (len > 0)
    return c;
  else
    return len;
}

/* Read a cooked string from a device */

int device_gets(int fd, char *s, size_t size)
{
  device_t *d;
  char *p;
  char c;
  int len;

  d = &device_table[fd];

  memset(s, 0, size);

  for (p = s; p < s + size - 1;)
  {
    while ((len = d->read(d->subdevice, &c, 1)) != 1);
    if (len < 0) return len;

    switch (c)
    {
      case '\r' :
      case '\n' :
        d->write(d->subdevice, "\r\n", 2);
        *p = '\n';
        return strlen(s);

      case '\b' :
        if (p > s)
        {
          *p-- = 0;
          d->write(d->subdevice, "\b \b", 3);
        }
        break;

      default :
        d->write(d->subdevice, &c, 1);
        *p++ = c;
        break;
    }
  }

  return strlen(s);
}
