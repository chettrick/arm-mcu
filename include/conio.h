/******************************************************************************/
/*                                                                            */
/*                   Simple serial console I/O routines.                      */
/*                                                                            */
/******************************************************************************/

// $Id: conio.h,v 1.1 2007-10-10 03:24:05 cvs Exp $

void conio_init(unsigned long int uartaddr, unsigned long int baudrate);

void putch(unsigned char c);

unsigned char getch(void);

void cputs(char *s);
