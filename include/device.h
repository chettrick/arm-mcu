/******************************************************************************/
/*                                                                            */
/*                 MCU independent Device Abstraction Layer                   */
/*                                                                            */
/******************************************************************************/

// $Id$

// Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef _DEVICE_H
#define _DEVICE_H

#include <unistd.h>
#include <sys/stat.h>

_BEGIN_STD_C

#ifdef CONIO_STDIO
#define MAX_DEVICES		2
#else
#ifndef MAX_DEVICES
#define MAX_DEVICES		16
#endif
#endif

#define DEVICE_NAME_SIZE	8

// Device names are of form <DEVICE>:<PARAMETER1><,PARAMETER2>...<,PARAMETERn>
// Only the first field is saved in the device table
typedef enum
{
  DEVICE_TYPE_UNUSED		= 0,
  DEVICE_TYPE_CHAR		= 1,
  DEVICE_TYPE_BLOCK		= 2,
  DEVICE_TYPE_DIRECTORY		= 3,
  DEVICE_TYPE_FILE		= 4,
} device_type_t;

typedef int (*device_open_fn_t)		(char *name, unsigned int *subdevice);

typedef int (*device_close_fn_t)	(unsigned int subdevice);

typedef int (*device_write_fn_t)	(unsigned int subdevice,
                                         char *buf,
                                         unsigned int count);

typedef int (*device_read_fn_t)		(unsigned int subdevice,
                                         char *buf,
                                         unsigned int count);

typedef int (*device_write_ready_fn_t)	(unsigned int subdevice);

typedef int (*device_read_ready_fn_t)	(unsigned int subdevice);

typedef int (*device_seek_fn_t)		(unsigned int subdevice,
                                         off_t pos,
                                         int whence);

typedef struct
{
  char name[DEVICE_NAME_SIZE+1];
  device_type_t type;
  unsigned int subdevice;
  device_open_fn_t open;
  device_close_fn_t close;
  device_write_fn_t write;
  device_read_fn_t read;
  device_write_ready_fn_t write_ready;
  device_read_ready_fn_t read_ready;
  device_seek_fn_t seek;
  int isopen;
  int flags;	// From open()
  int mode;	// From open()
} device_t;

// Device registration functions

int device_register_char(char *name,
                         unsigned int subdevice,
                         device_open_fn_t open,
                         device_close_fn_t close,
                         device_write_fn_t write,
                         device_read_fn_t read,
                         device_write_ready_fn_t write_ready,
                         device_read_ready_fn_t read_ready);

int device_register_char_fd(int fd,
                            unsigned int subdevice,
                            device_write_fn_t write,
                            device_read_fn_t read,
                            device_write_ready_fn_t write_ready,
                            device_read_ready_fn_t read_ready);

int device_register_block(char *name,
                          device_open_fn_t open,
                          device_close_fn_t close,
                          device_write_fn_t write,
                          device_read_fn_t read,
                          device_seek_fn_t seek);

int device_unregister(int fd);

int device_lookup(char *name);

// I/O method functions

int device_open(char *name, int flags, int mode);
int device_close(int fd);
int device_ready_read(int fd);
int device_ready_write(int fd);
int device_read_raw(int fd, char *s, unsigned int count);
int device_read_cooked(int fd, char *s, unsigned int count);
int device_read(int fd, char *s, unsigned int count);
int device_getc(int fd);
int device_write_raw(int fd, char *s, unsigned int count);
int device_write_cooked(int fd, char *s, unsigned int count);
int device_write(int fd, char *s, unsigned int count);
int device_putc(int fd, char c);

// File system support method functions

int device_isatty(int fd);
off_t device_seek(int fd, off_t pos, int whence);
int device_stat(int fd, struct stat *st);

// Convenience macros, vaguely inspired by Turbo C and Turbo Pascal

#define keypressed(...)	device_ready_read(0)
#define getch(...)	device_getc(0)
#define putch(c)	device_putc(1, c)
#define cgets(s, count)	device_read(0, s, count)
#define cputs(s)	device_write(1, s, strlen(s))

_END_STD_C
#endif
