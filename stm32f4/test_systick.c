/* Simple timer interrupt test program */

// $Id: test_systick.c 3164 2011-10-17 10:54:39Z svn $

static const char revision[] = "$Id: test_systick.c 3164 2011-10-17 10:54:39Z svn $";

#include <cpu.h>
#include <stdio.h>

volatile int TimerCounter = 0;
volatile int TimerFlag = FALSE;

void SysTick_Handler(void)
{
  if (++TimerCounter == 20)
  {
    TimerCounter = 0;
    TimerFlag = TRUE;
  }
}

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);

  serial_stdio(CONSOLE_PORT);

  puts("\033[H\033[2JSTM32F4 System Tick Interrupt Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", CPUFREQ, __VERSION__);

// Configure LED(s)

  LEDS_initialize();
  LEDS_set(LED2|LED4|LED6|LED8);

// Initialize System Tick with 50ms time interval

  SysTick_Config(SystemCoreClock / 20);

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
