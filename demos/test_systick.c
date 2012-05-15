/* Simple timer interrupt test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <stdio.h>

#define SYSTICKRATE	100

_BEGIN_STD_C

volatile int TimerCounter = 0;
volatile int TimerFlag = FALSE;

void SysTick_Handler(void)
{
  if (++TimerCounter == SYSTICKRATE)
  {
    TimerCounter = 0;
    TimerFlag = TRUE;
  }
}

_END_STD_C

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);

#ifdef CONSOLE_USB
  usb_serial_stdio(NULL);
  getch();
#else
  serial_stdio(CONSOLE_PORT);
#endif

  printf("\033[H\033[2J%s System Tick Interrupt Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s %s %s\n\n", CPUFREQ, __COMPILER__, __VERSION__, __ABI__);

// Configure LED(s)

  LEDS_initialize();
  LEDS_set(LED2|LED4|LED6|LED8);

// Initialize System Tick

  SysTick_Config(SystemCoreClock / SYSTICKRATE);

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
