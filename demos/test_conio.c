/* Simple console I/O test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <conio.h>

int main(void)
{
  int i;
  char buf[256];
  int x, y;

  cpu_init(DEFAULT_CPU_FREQ);
  conio_init(CONSOLE_PORT);

  printf("\033[H\033[2J%s Console I/O Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  puts(revision);
  printf("\nCPU Freq:%d Hz  Compiler:%s %s %s\n\n", SystemCoreClock, __COMPILER__, __VERSION__, __ABI__);

// Test putchar()

  for (i = 'A'; i < 'Z'; i++)
    putchar(i);

  putchar('\n');
  putchar('\n');

// Test puts()

  for (i = 0; i < 10; i++)
  {
    sprintf(buf, "The value of the variable i is currently, now, until the next iteration, %d", i);
    puts(buf);
  }

// Test keypressed() and getchar()

  printf("\nPress ^C to continue: ");

  for (;;)
  {
    printf("|\b/\b-\b\\\b");

    if (keypressed())
    {
      if (getchar() == 3)
        break;
      else
        putchar('.');
    }
  }

  putchar('\n');
  putchar('\n');

// Test gets()

  for (;;)
  {
    printf("[gets] Enter a string: ");
    gets(buf);
    if (strlen(buf)) if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;
    if (!strcasecmp(buf, "next")) break;
    printf("\n[gets] You entered %u bytes, '%s'\n\n", (unsigned) strlen(buf), buf);
  }

  putchar('\n');

// Test numeric input

  for (;;)
  {
    printf("Enter two numbers: ");

    gets(buf);
    sscanf(buf, "%d %d", &x, &y);

    printf("You entered %d and %d\n\n", x, y);

    if ((x == 0) && (y == 0)) break;
  }

  puts("End of program");
  for (;;);
}
