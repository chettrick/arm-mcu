/* Simple console I/O functions--a lightweight alternative to newlib stdio */

// $Id$

#ifndef _CONIO_H
#define _CONIO_H

#include <_ansi.h>
#include <stdarg.h>

_BEGIN_STD_C

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

void conio_init(const char *console);	// Initialize console

int keypressed(void);			// Check for data ready

int getch(void);			// Get a character (cooked)

void putch(char c);			// Write a character

int cgets(char *s, int size);		// Get a line of text

void cputs(const char *s);		// Write a string

int cprintf(const char *format, ...);	// Write formatted text

int csprintf(char *out, const char *format, ...);

int csscanf(const char *str, const char *format, ...);

// Emulate C standard I/O

#define getchar()	getch()
#define putchar(x)	putch(x)
#define gets(x)		cgets(x, sizeof(x))
#define puts(x)		{ cputs(x); putch('\n'); }
#define printf(...)	cprintf(__VA_ARGS__)
#define sprintf(...)	csprintf(__VA_ARGS__)
#define sscanf(...)	csscanf(__VA_ARGS__)

_END_STD_C
#endif
