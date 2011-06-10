/* Simple timer interrupt test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <stdio.h>

#define TRUE	1
#define	FALSE	0

volatile int TimerCounter = 0;
volatile int TimerFlag = FALSE;

void SysTick_Handler(void)
{
  if (++TimerCounter == 10)
  {
    TimerCounter = 0;
    TimerFlag = TRUE;
  }
}

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);
  serial_stdio(CONSOLE_PORT, 115200);

  puts("\033[H\033[2JEFM32 System Tick Interrupt Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", CPUFREQ, __VERSION__);

// Configure LED(s)

  LEDS_initialize();
  LEDS_set(0x55555555);

// Initialize System Tick with 100ms time interval

  SysTick_Config(SystemCoreClock / 10);

// Display "Tick..." every second

  for (;;)
  {
    if (TimerFlag)
    {
      TimerFlag = FALSE;

      puts("Tick...");
      fflush(stdout);

      LEDS_set(~LEDS_get());
    }
  }
}
