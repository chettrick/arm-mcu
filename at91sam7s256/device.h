/******************************************************************************/
/*                                                                            */
/*                 MCU independent Device Abstraction Layer                   */
/*                                                                            */
/******************************************************************************/

// $Id$

#include <unistd.h>
#include <sys/stat.h>

#define MAX_DEVICES		16
#define DEVICE_NAME_SIZE	9

typedef enum
{
  DEVICE_TYPE_UNUSED		= 0,
  DEVICE_TYPE_CHAR		= 1,
  DEVICE_TYPE_BLOCK		= 2,
  DEVICE_TYPE_DIRECTORY		= 3,
  DEVICE_TYPE_FILE		= 4,
} device_type_t;

typedef int (*device_init_t)		(unsigned subdevice, void *settings);
typedef int (*device_write_t)		(unsigned subdevice, char *buf, unsigned int count);
typedef int (*device_read_t)		(unsigned subdevice, char *buf, unsigned int count);
typedef int (*device_write_ready_t)	(unsigned subdevice);
typedef int (*device_read_ready_t)	(unsigned subdevice);
typedef int (*device_seek_t)		(unsigned subdevice, off_t pos, int whence);

typedef struct
{
  char name[DEVICE_NAME_SIZE];
  device_type_t type;
  unsigned subdevice;
  void *settings;
  device_init_t init;
  device_write_t write;
  device_read_t read;
  device_write_ready_t write_ready;
  device_read_ready_t read_ready;
  device_seek_t seek;
  int flags;
} device_t;

// Device registration functions

int device_register_char(char *name, unsigned subdevice, void *settings,
                         device_init_t init, device_write_t write, device_read_t read,
                         device_write_ready_t write_ready, device_read_ready_t read_ready);

int device_register_char_fd(char *name, int fd, unsigned subdevice, void *settings,
                            device_init_t init, device_write_t write, device_read_t read,
                            device_write_ready_t write_ready, device_read_ready_t read_ready);

int device_register_block(char *name, unsigned subdevice, void *settings,
                          device_init_t init, device_write_t write, device_read_t read,
                          device_seek_t seek);

int device_unregister(int fd);

int device_lookup(char *name);

// I/O method functions

int device_open(char *name, int flags, int mode);
int device_close(int fd);
int device_init(int fd, void *settings);
int device_ready_read(int fd);
int device_ready_write(int fd);
int device_read(int fd, char *s, unsigned int count);
int device_write(int fd, char *s, unsigned int count);
int device_getc(int fd);
int device_putc(int fd, char c);

// File system support method functions

int device_isatty(int fd);
off_t device_seek(int fd, off_t pos, int whence);
int device_stat(int fd, struct stat *st);

// Convenience macros, vaguely inspired by Turbo C and Turbo Pascal

#define keypressed(...)	(device_ready_read(fileno(stdin)))
#define getch(...)	(device_getc(fileno(stdin)))
#define putch(c)	(device_putc(fileno(stdout), c))
#define cgets(s, count)	(device_read(fileno(stdin), s, count))
#define cputs(s)	(device_write(fileno(stdout), s, strlen(s)))
