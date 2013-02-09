/* Simple console I/O functions--a lightweight alternative to newlib stdio */

// $Id$

// Copyright (C)2013, Philip Munts, President, Munts AM Corp.
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

#ifndef _CONIO_H
#define _CONIO_H

#include <_ansi.h>
#include <stdarg.h>

_BEGIN_STD_C

// Include this *after* cpu.h and stdio.h so that the following
// macro undef's work properly.

// Undefine macros from arm.h

#undef printf
#undef fprintf
#undef sprintf
#undef snprintf
#undef asprintf
#undef asnprintf
#undef scanf
#undef sscanf
#undef fscanf

// Undefine macros from device.h

#undef keypressed
#undef getch
#undef putch
#undef cgets
#undef cputs

// Undefine macros from errno.h

#undef errno

// Undefine macros from stdio.h

#undef getchar
#undef putchar

void conio_init(const char *console);	// Initialize console

extern int conio_errno;			// Replacement errno

int keypressed(void);			// Check for data ready

int getch(void);			// Get a character (cooked)

void putch(char c);			// Write a character

int cgets(char *s, int size);		// Get a line of text

void cputs(const char *s);		// Write a string

int cprintf(const char *format, ...);	// Write formatted text

int csprintf(char *out, const char *format, ...);

int csscanf(const char *str, const char *format, ...);

int lightweight_atoi(const char *s);

char *lightweight_strerror(int e);

// Emulate C standard I/O

#define serial_stdio(x)	conio_init(x)

#define errno		conio_errno
#define getchar()	getch()
#define putchar(x)	putch(x)
#define gets(x)		cgets(x, sizeof(x))
#define puts(x)		{ cputs(x); putch('\n'); }
#define printf(...)	cprintf(__VA_ARGS__)
#define sprintf(...)	csprintf(__VA_ARGS__)
#define sscanf(...)	csscanf(__VA_ARGS__)
#define atoi(x)		lightweight_atoi(x)
#define strerror(x)	lightweight_strerror(x)

_END_STD_C
#endif
