/******************************************************************************/
/*                                                                            */
/*                 MCU independent Device Abstraction Layer                   */
/*                                                                            */
/******************************************************************************/

// $Id$

static const char revision[] = "$Id$";

#include <assert.h>
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

/* Register a character device driver to the next available file descriptor */

int device_register_char(char *name, unsigned subdevice, void *settings,
                         device_init_t init, device_write_t write, device_read_t read,
                         device_write_ready_t write_ready, device_read_ready_t read_ready)
{
  int fd;

  errno = 0;

  if (name) if (device_lookup(name) >= 0)
  {
    errno = EEXIST;
    return -1;
  }
  
  for (fd = 3; fd < MAX_DEVICES; fd++)
    if (device_table[fd].type == DEVICE_TYPE_UNUSED)
    {
      memset(&device_table[fd], 0, sizeof(device_t));
      if (name) strlcpy(device_table[fd].name, name, sizeof(device_table[fd].name) - 1);
      device_table[fd].type = DEVICE_TYPE_CHAR;
      device_table[fd].subdevice = subdevice;
      device_table[fd].settings = settings;
      device_table[fd].init = init;
      device_table[fd].write = write;
      device_table[fd].read = read;
      device_table[fd].write_ready = write_ready;
      device_table[fd].read_ready = read_ready;

      return fd;
    }

  errno = ENOMEM;
  return -1;
}

/* Register a character device driver to a specific file descripter */

int device_register_char_fd(char *name, int fd, unsigned subdevice, void *settings,
                            device_init_t init, device_write_t write, device_read_t read,
                            device_write_ready_t write_ready, device_read_ready_t read_ready)
{
  errno = 0;

  if (device_table[fd].type != DEVICE_TYPE_UNUSED)
  {
    errno = EEXIST;
    return -1;
  }

  if (name) if (device_lookup(name) >= 0)
  {
    errno = EEXIST;
    return -1;
  }

  if (fd >= MAX_DEVICES)
  {
    errno = EINVAL;
    return -1;
  }

  memset(&device_table[fd], 0, sizeof(device_t));
  if (name) strlcpy(device_table[fd].name, name, sizeof(device_table[fd].name) - 1);
  device_table[fd].type = DEVICE_TYPE_CHAR;
  device_table[fd].subdevice = subdevice;
  device_table[fd].settings = settings;
  device_table[fd].init = init;
  device_table[fd].write = write;
  device_table[fd].read = read;
  device_table[fd].write_ready = write_ready;
  device_table[fd].read_ready = read_ready;

  return fd;
}

/* Register a block device driver to the next available file descriptor */

int device_register_block(char *name, unsigned subdevice, void *settings,
                          device_init_t init, device_write_t write, device_read_t read,
                          device_seek_t seek)
{
  int fd;

  errno = 0;

  if (device_lookup(name) >= 0)
  {
    errno = EEXIST;
    return -1;
  }
  
  for (fd = 3; fd < MAX_DEVICES; fd++)
    if (device_table[fd].type == DEVICE_TYPE_UNUSED)
    {
      memset(&device_table[fd], 0, sizeof(device_t));
      if (name) strlcpy(device_table[fd].name, name, sizeof(device_table[fd].name) - 1);
      device_table[fd].type = DEVICE_TYPE_BLOCK;
      device_table[fd].subdevice = subdevice;
      device_table[fd].settings = settings;
      device_table[fd].init = init;
      device_table[fd].write = write;
      device_table[fd].read = read;
      device_table[fd].seek = seek;

      return fd;
    }

  errno = ENOMEM;
  return -1;
}

/* Unregister a device driver */

int device_unregister(fd)
{
  errno = 0;

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno = ENODEV;
    return -1;
  }

  if (fd >= MAX_DEVICES)
  {
    errno = EINVAL;
    return -1;
  }

  memset(&device_table[fd], 0, sizeof(device_t));
  return 0;
}

/* Lookup a device */

int device_lookup(char *name)
{
  int fd;

  errno = 0;

  for (fd = 0; fd < MAX_DEVICES; fd++)
    if (!strcasecmp(device_table[fd].name, name))
      return fd;

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

  device_table[fd].flags = flags;

  status = device_table[fd].init(device_table[fd].subdevice, device_table[fd].settings);
  if (status < 0) return status;

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
 
  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno = ENODEV;
    return -1;
  }

  device_table[fd].flags = 0;
  return 0;
}

/* Initialize a device */

int device_init(int fd, void *settings)
{
  errno = 0;

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno = ENODEV;
    return -1;
  }

  if (device_table[fd].init == NULL)
  {
    errno = EIO;
    return -1;
  }

  device_table[fd].settings = settings;

  return device_table[fd].init(device_table[fd].subdevice, settings);
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
 
  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
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
 
  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
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

/* Read uncooked input from a device (whatever is available) */

int device_read_raw(int fd, char *s, unsigned int count)
{
  errno = 0;

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno = ENODEV;
    return -1;
  }

  if (device_table[fd].read == NULL)
  {
    errno = EIO;
    return -1;
  }

  memset(s, 0, count);
  return device_table[fd].read(device_table[fd].subdevice, s, count);
}

/* Read cooked input from a device */

int device_read_cooked(int fd, char *s, unsigned int count)
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

  if (d->type == DEVICE_TYPE_UNUSED)
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

// Handle cooked character device input here

  for (p = s; p < s + count - 1;)
  {
    while ((len = d->read(d->subdevice, &c, 1)) == 0);
    if (len < 0) return len;

    switch (c)
    {
      case '\r' :
      case '\n' :
        if (fd > 0)
          device_write_raw(fd, "\r\n", 2);
        else
          device_write_raw(1, "\r\n", 2);

        *p = '\n';

        return strlen(s);

      case '\b' :
      case 127 :
        if (p > s)
        {
          *p-- = 0;

          if (fd > 0)
            device_write_raw(fd, "\b \b", 3);
          else
            device_write_raw(1, "\b \b", 3);
        }
        break;

      default :
        if (fd > 0)
          device_write_raw(fd, &c, 1);
        else
          device_write_raw(1, &c, 1);

        *p++ = c;
        break;
    }
  }

  return strlen(s);
}

/* Read input from a device */

int device_read(int fd, char *s, unsigned int count)
{
  errno = 0;

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno = EINVAL;
    return -1;
  }

  if ((device_table[fd].type != DEVICE_TYPE_CHAR) || (device_table[fd].flags & O_BINARY))
    return device_read_raw(fd, s, count);
  else
    return device_read_cooked(fd, s, count);
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

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
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

/* Write uncooked output to a device */

int device_write_raw(int fd, char *s, unsigned int count)
{
  int len;
  int i;

  errno = 0;

// Validate file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno = ENODEV;
    return -1;
  }

  if (device_table[fd].write == NULL)
  {
    errno = EIO;
    return -1;
  }

// Dispatch raw data to device driver.  Keep trying if less than the whole
// buffer is transferred.

  for (i = 0; i < count;)
  {
    len = device_table[fd].write(device_table[fd].subdevice, s, count - i);
    if (len < 0) return len;

    s += len;
    i += len;
  }

  return count;
}

/* Write cooked (CR before LF) output to a device */

int device_write_cooked(int fd, char *s, unsigned int count)
{
  int len;
  int i;
  char *p;

  errno = 0;

// Validate file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno = ENODEV;
    return -1;
  }

  if (device_table[fd].write == NULL)
  {
    errno = EIO;
    return -1;
  }

// Handle cooked character device output here

  for (i = 0; i < count;)
  {
    p = memchr(s, '\n', count - i);

    if (p == NULL)
    {
      len = device_write_raw(fd, s, count);	// Write everything
      if (len < 0) return len;

      i += len;
      s += len;
    }
    else
    {
      len = device_write_raw(fd, s, p - s);	// Write everything up to LF
      if (len < 0) return len;

      i += len;
      s += len;

      len = device_write_raw(fd, "\r\n", 2);	// Write CR/LF
      if (len < 0) return len;

      i++;
      s++;
    }
  }

  return count;
}

/* Write to a device */

int device_write(int fd, char *s, unsigned int count)
{
  errno = 0;

// Validate file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno = EINVAL;
    return -1;
  }

  if ((device_table[fd].type != DEVICE_TYPE_CHAR) || (device_table[fd].flags & O_BINARY))
    return device_write_raw(fd, s, count);
  else
    return device_write_cooked(fd, s, count);
}
  
/* Write a single character to a device */

int device_putc(int fd, char c)
{
  return device_write(fd, &c, 1);
}

/* Is this file descriptor a character device? */

int device_isatty(int fd)
{
  errno = 0;

// Validate file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno = ENODEV;
    return -1;
  }

  return (device_table[fd].type == DEVICE_TYPE_CHAR);
}

/* Return file information */

int device_stat(int fd, struct stat *st)
{
  errno = 0;

// Validate file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno = ENODEV;
    return -1;
  }

  memset(st, 0, sizeof(struct stat));

  switch (device_table[fd].type)
  {
    case DEVICE_TYPE_CHAR :
      st->st_mode = S_IFCHR;
      break;

    case DEVICE_TYPE_BLOCK :
      st->st_mode = S_IFBLK;
      break;

    case DEVICE_TYPE_DIRECTORY :
      st->st_mode = S_IFDIR;
      break;

    case DEVICE_TYPE_FILE :
      st->st_mode = S_IFREG;
      break;

    default :
      assert(0);
  }

  return 0;
}

/* Seek to position in file */

off_t device_seek(int fd, off_t pos, int whence)
{
  errno = 0;

// Validate file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno = ENODEV;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_CHAR)
  {
    errno = EINVAL;
    return -1;
  }

  return device_table[fd].seek(device_table[fd].subdevice, pos, whence);
}
