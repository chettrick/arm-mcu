/******************************************************************************/
/*                                                                            */
/*                   Simple serial console I/O routines.                      */
/*                                                                            */
/******************************************************************************/

// $Id: conio.h,v 1.2 2007-10-29 16:12:18 cvs Exp $

void conio_init(unsigned long int uartaddr, unsigned long int baudrate);

void putch(unsigned char c);

unsigned char getch(void);

unsigned char keypressed(void);

void cputs(char *s);
