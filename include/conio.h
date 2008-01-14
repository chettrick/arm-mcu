/******************************************************************************/
/*                                                                            */
/*                   Simple serial console I/O routines.                      */
/*                                                                            */
/******************************************************************************/

// $Id: conio.h,v 1.3 2008-01-14 11:13:38 cvs Exp $

void conio_init(unsigned port, unsigned long int baudrate);

void putch(unsigned char c);

unsigned char getch(void);

unsigned char keypressed(void);

void cputs(char *s);
