// Semi-hosting I/O services

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

// These services ONLY work in debug mode.  If your program calls any of these,
// it will NOT work unless you are debugging.

// Be sure to issue "monitor arm semihosting enable" in gdb before starting
// your program.

#include <fcntl.h>
#include <string.h>

#include <cpu.h>

void *__semihosting(uint32_t op, void *arg)
{
#ifdef __thumb2__
  asm("push {LR}; bkpt 0xAB; pop {PC}");
#else
  asm("push {LR}; svc 0xAB; pop {PC}");
#endif
}

int semihosting_register(char *name)
{
  return device_register_char(name, 0, semihosting_open, semihosting_close,
    semihosting_write, semihosting_read,
    semihosting_write_ready, semihosting_read_ready);
}

int semihosting_stdio(char *name)
{
  unsigned int subdevice;

  if (semihosting_open(name, &subdevice))
    return -1;

  // Nuke existing stdin, stdout, stderr

  device_unregister(0);
  device_unregister(1);
  device_unregister(2);

  // Register new stdin, stdout, stderr

  device_register_char_fd(0, subdevice, NULL, semihosting_read, NULL, semihosting_read_ready);
  device_register_char_fd(1, subdevice, semihosting_write, NULL, semihosting_write_ready, NULL);
  device_register_char_fd(2, subdevice, semihosting_write, NULL, semihosting_write_ready, NULL);

  // Put stdin in binary mode, because of the limitations of semihosting in OpenOCD.
  // We need to use the input line editor in OpenOCD instead of ours in device.c

  fcntl(0, F_SETFL, O_BINARY);

  return 0;
}

int semihosting_open(char *name, unsigned int *subdevice)
{
  int devicenamelen;
  uint32_t open_parms[3];
  int status;

// Skip past device name, to the host pathname

  devicenamelen = strcspn(name, ":");
  if (devicenamelen > DEVICE_NAME_SIZE)
  {
    errno_r = EINVAL;
    return -1;
  }

  name += devicenamelen + 1;

  open_parms[0] = (uint32_t) name;
  open_parms[1] = 2;
  open_parms[2] = strlen(name);

  status = (int) __semihosting(SYS_OPEN, open_parms);

  if (status < 0)
  {
    errno_r = EIO;
    return -1;
  }
  else
  {
    *subdevice = status;
    errno_r = 0;
    return 0;
  }
}

int semihosting_close(unsigned int fd)
{
  uint32_t close_parms[1];
  int status;

  close_parms[0] = fd;

  status = (int) __semihosting(SYS_CLOSE, close_parms);

  if (status < 0)
  {
    errno_r = EIO;
    return -1;
  }
  else
  {
    errno_r = 0;
    return 0;
  }
}

int semihosting_read(unsigned int fd, char *buf, unsigned int count)
{
  uint32_t read_parms[3];
  int status;

  errno_r = 0;

  read_parms[0] = fd;
  read_parms[1] = (uint32_t) buf;
  read_parms[2] = count;

  status = (int) __semihosting(SYS_READ, read_parms);

  if (status < 0)
  {
    errno_r = EIO;
    return status;
  }
  else
    return count - status;
}

int semihosting_write(unsigned int fd, char *buf, unsigned int count)
{
  uint32_t write_parms[3];
  int status;

  errno_r = 0;

  write_parms[0] = fd;
  write_parms[1] = (uint32_t) buf;
  write_parms[2] = count;

  status = (int) __semihosting(SYS_WRITE, write_parms);

  if (status < 0)
  {
    errno_r = EIO;
    return status;
  }
  else
    return count - status;
}

int semihosting_read_ready(unsigned int fd)
{
  return true;
}

int semihosting_write_ready(unsigned int fd)
{
  return true;
}
