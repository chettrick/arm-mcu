/* Simple serial console I/O test program */

// $Id: test_conio.c,v 1.7 2008-08-14 20:08:18 cvs Exp $

#include <cpu.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
  int i;
  char buf[256];
  int x, y;

  cpu_init(DEFAULT_CPU_FREQ);
  serial_stdio(0, 19200);

  puts("\033[H\033[2JSTR912FAW44 Console I/O Test (" __DATE__ " " __TIME__ ")\n");

// Test putch()

  for (i = 'A'; i < 'Z'; i++)
    putch(i);

  putch('\n');
  putch('\n');

// Test cputs()

  for (i = 0; i < 10; i++)
  {
    sprintf(buf, "The value of the variable i is currently, now, until the next iteration, %d\n", i);
    cputs(buf);
  }

// Test keypressed() and getch()

  cputs("\nPress ^C to continue: ");

  for (;;)
  {
    cputs("|\b/\b-\b\\\b");

    if (keypressed())
    {
      if (getch() == 3)
        break;
      else
        putch('.');
    }
  }

  putch('\n');
  putch('\n');

// Test cputs() and cgets()

  for (;;)
  {
    cputs("[cgets] Enter a string: ");
    cgets(buf, sizeof(buf));
    if (strlen(buf)) if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;
    if (!strcasecmp(buf, "next")) break;
    printf("[cgets] You entered %ld bytes, '%s'\n\n", strlen(buf), buf);
  }

// Test putchar()

  putchar('\n');

  for (i = 'a'; i < 'z'; i++)
    putchar(i);

  putchar('\n');
  putchar('\n');

// Test printf() and fgets()

  for (;;)
  {
    printf("[fgets] Enter a string: ");
    fflush(stdout);
    fgets(buf, sizeof(buf), stdin);
    if (strlen(buf)) if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;
    if (!strcasecmp(buf, "next")) break;
    printf("[fgets] You entered %ld bytes, '%s'\n\n", strlen(buf), buf);
  }

  putchar('\n');

// Test scanf()

  for (;;)
  {
    printf("Enter two numbers: ");
    fflush(stdout);

    fflush(stdin);
    scanf("%d %d", &x, &y);
    printf("You entered %d and %d\n", x, y);
  }
}
