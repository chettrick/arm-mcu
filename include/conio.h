/******************************************************************************/
/*                                                                            */
/*                   Simple serial console I/O routines.                      */
/*                                                                            */
/******************************************************************************/

// $Id: conio.h,v 1.4 2008-03-24 11:17:21 cvs Exp $

void conio_init(unsigned port, unsigned long int baudrate);

void putch(unsigned char c);

unsigned char getch(void);

unsigned char keypressed(void);

void cputs(char *s);

void cgets(char *s, int bufsize);
