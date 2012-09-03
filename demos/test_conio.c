/* Simple console I/O test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  int i;
  char buf[256];
  int x, y;

  cpu_init(DEFAULT_CPU_FREQ);
  conio_init(CONSOLE_PORT);

  cprintf("\033[H\033[2J%s Console I/O Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  cputs(revision);
  cprintf("\n\nCPU Freq:%d Hz  Compiler:%s %s %s\n\n", SystemCoreClock, __COMPILER__, __VERSION__, __ABI__);

// Test putch()

  for (i = 'A'; i < 'Z'; i++)
    putch(i);

  putch('\n');
  putch('\n');

// Test cputs()

  for (i = 0; i < 10; i++)
  {
    csprintf(buf, "The value of the variable i is currently, now, until the next iteration, %d\n", i);
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
    cprintf("[cgets] You entered %u bytes, '%s'\n\n", (unsigned) strlen(buf), buf);
  }

  putch('\n');

// Test numeric input

  for (;;)
  {
    cputs("Enter two numbers: ");

    cgets(buf, sizeof(buf));
    csscanf(buf, "%d %d", &x, &y);

    cprintf("You entered %d and %d\n\n", x, y);

    if ((x == 0) && (y == 0)) break;
  }

  cputs("End of program\n");
  exit(0);
}
