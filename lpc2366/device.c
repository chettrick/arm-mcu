/******************************************************************************/
/*                                                                            */
/*              Device abstraction layer for the LPC2366 ARM MCU              */
/*                                                                            */
/******************************************************************************/

// $Id$

#include <cpu.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

// Some toolchains don't define O_BINARY

#ifndef O_BINARY
#define O_BINARY	0x10000
#endif

// Redefine errno, because newlib normally defines it with a macro

#undef errno
extern int errno;

// This is the device table

static device_t device_table[MAX_DEVICES];

/* Register a device driver to the next available file descriptor */

int device_register(char *name, unsigned subdevice, void *settings,
                    device_init_t init, device_write_t write, device_read_t read,
                    device_write_ready_t write_ready, device_read_ready_t read_ready)
{
  int d;

  errno = 0;

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
      device_table[d].flags = 0;
      return 0;
    }

  errno = ENOMEM;
  return -1;
}

/* Register a device driver to a specific file descripter */

int device_register_fd(char *name, int fd, unsigned subdevice, void *settings,
                       device_init_t init, device_write_t write, device_read_t read,
                       device_write_ready_t write_ready, device_read_ready_t read_ready)
{
  errno = 0;

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
  device_table[fd].flags = 0;

  return 0;
}

/* Unregister a device driver */

int device_unregister(char *name)
{
  int d;

  errno = 0;

  d = device_lookup(name);
  if (d < 0) return d;

  memset(&device_table[d], 0, sizeof(device_t));
  return 0;
}

/* Lookup a device */

int device_lookup(char *name)
{
  int d;

  errno = 0;

  for (d = 0; d < MAX_DEVICES; d++)
    if (!strcasecmp(device_table[d].name, name))
      return d;

  errno = ENODEV;
  return -1;
}

/* Open a device */

int device_open(char *name, int flags, int mode)
{
  int fd, status;

  errno = 0;

  fd = device_lookup(name);
  if (fd < 0) return fd;

  status = device_table[fd].init(device_table[fd].subdevice, device_table[fd].settings);
  if (status < 0) return status;

  device_table[fd].flags = flags;
  return fd;
}

/* Close a device */

int device_close(int fd)
{
  errno = 0;

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno = EINVAL;
    return -1;
  }
 
  if (device_table[fd].name[0] == 0)
  {
    errno = ENODEV;
    return -1;
  }

  device_table[fd].flags = 0;
  return 0;
}

/* Return TRUE if the device has received data available */

int device_ready_read(int fd)
{
  errno = 0;

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno = EINVAL;
    return -1;
  }
 
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

/* Return TRUE if the device is ready to accept transmit data */

int device_ready_write(int fd)
{
  errno = 0;

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno = EINVAL;
    return -1;
  }
 
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

/* Read from a device */

int device_read(int fd, char *s, unsigned int count)
{
  device_t *d;
  char *p;
  char c;
  int len;

  errno = 0;

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno = EINVAL;
    return -1;
  }

  d = &device_table[fd];

  if (d->name[0] == 0)
  {
    errno = ENODEV;
    return -1;
  }

  if (d->read == NULL)
  {
    errno = EIO;
    return -1;
  }

  memset(s, 0, count);

// Pass raw read directly to device driver

  if (d->flags & O_BINARY)
    return d->read(d->subdevice, s, count);

// Handle cooked input here

  for (p = s; p < s + count - 1;)
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

/* Write to a device */

int device_write(int fd, char *s, unsigned int count)
{
  int i;

  errno = 0;

// Validate file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno = EINVAL;
    return -1;
  }

  if (device_table[fd].name[0] == 0)
  {
    errno = ENODEV;
    return -1;
  }

  if (device_table[fd].write == NULL)
  {
    errno = EIO;
    return -1;
  }

// Pass binary write directly to device driver

  if (device_table[fd].flags & O_BINARY)
    return device_table[fd].write(device_table[fd].subdevice, s, count);

// Handle cooked (CR inserted before each LF) output here

  for (i = 0; i < count; i++)
  {
    if (*s == '\n') if (device_table[fd].write(device_table[fd].subdevice, "\r", 1) != 1)
      return -1;

    if (device_table[fd].write(device_table[fd].subdevice, s, 1) != 1)
      return -1;

    s++;
  }

  return count;
}
  
/* Read a single unbuffered, unechoed character from a device */

int device_getc(int fd)
{
  int len;
  char c;

  errno = 0;

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno = EINVAL;
    return -1;
  }

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

/* Write a single character to a device */

int device_putc(int fd, char c)
{
  return device_write(fd, &c, 1);
}
