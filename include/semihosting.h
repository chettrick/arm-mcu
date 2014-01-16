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

// Semi-hosting operations -- From "ARM Compiler toolchain Developing
// Software for ARM Processors,Version 5.03"

#define SYS_OPEN		0x01
#define SYS_CLOSE		0x02
#define SYS_WRITEC		0x03
#define SYS_WRITE0		0x04
#define SYS_WRITE		0x05
#define SYS_READ		0x06
#define SYS_READC		0x07
#define SYS_ISERROR		0x08
#define SYS_ISTTY		0x09
#define SYS_SEEK		0x0A
#define SYS_FLEN		0x0C
#define SYS_TMPNAM		0x0D
#define SYS_REMOVE		0x0E
#define SYS_CLOCK		0x10
#define SYS_TIME		0x11
#define SYS_SYSTEM		0x12
#define SYS_ERRNO		0x13
#define SYS_GET_CMDLINE		0x15
#define SYS_HEAPINFO		0x16
#define SYS_ELAPSED		0x30
#define SYS_TICKFREQ		0x31

// Function prototypes

void *__semihosting(uint32_t op, void *arg) __attribute__((naked));

int semihosting_register(char *name);
int semihosting_stdio(char *name);
int semihosting_open(char *name, unsigned int *subdevice);
int semihosting_close(unsigned int fd);
int semihosting_read(unsigned int fd, char *buf, unsigned int count);
int semihosting_write(unsigned int fd, char *buf, unsigned int count);
int semihosting_read_ready(unsigned int fd);
int semihosting_write_ready(unsigned int fd);
