/******************************************************************************/
/*                                                                            */
/*                   Simple serial console I/O routines.                      */
/*                                                                            */
/******************************************************************************/

// $Id$

void conio_init(unsigned port, unsigned long int baudrate);

void putch(unsigned char c);

unsigned char getch(void);

unsigned char keypressed(void);

void cputs(char *s);

void cgets(char *s, int bufsize);
