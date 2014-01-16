/* Simple console I/O functions--a lightweight alternative to newlib stdio */

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

#ifndef _CONIO_H
#define _CONIO_H

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

// Undefine macros from errno.h

#undef errno

// Undefine macros from stdio.h

#undef fflush
#undef getchar
#undef putchar
#undef gets
#undef puts

int cprintf(const char *format, ...);

int csprintf(char *out, const char *format, ...);

int csscanf(const char *str, const char *format, ...);

int lightweight_atoi(const char *s);

void lightweight_exit(int status);

char *lightweight_strerror(int e);

extern int lightweight_errno;

// Emulate C standard I/O

#define fflush(x)
#define getchar()	getch()
#define putchar(x)	putch(x)
#define gets(x)		cgets(x, sizeof(x))
#define puts(x)		{ cputs((char *) x); putch('\n'); }
#define printf(...)	cprintf(__VA_ARGS__)
#define sprintf(...)	csprintf(__VA_ARGS__)
#define sscanf(...)	csscanf(__VA_ARGS__)
#define atoi(x)		lightweight_atoi(x)
#define strerror(x)	lightweight_strerror(x)
#define errno		lightweight_errno
#define exit(x)		lightweight_exit(x)

#ifndef EOF
#define EOF		(-1)
#endif

_END_STD_C
#endif
