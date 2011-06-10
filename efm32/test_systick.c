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

#ifdef EFM32_G8XX_STK
  /* Enable GPIO */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Configure GPIO port C 0-3 as LED control outputs */
  GPIO_PinModeSet(gpioPortC, 0, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortC, 1, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortC, 2, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortC, 3, gpioModePushPull, 1);

  /* Set initial LED states */
  GPIO_PortOutSetVal(gpioPortC, 0x05, 0xf);
#endif

// Initialize System Tick with 100ms time interval

  SysTick_Config(SystemCoreClock / 10);

// Display "Tick..." every second

  for (;;)
  {
    if (TimerFlag)
    {
      TimerFlag = FALSE;

#ifdef EFM32_G8XX_STK
      GPIO_PortOutSetVal(gpioPortC, ~GPIO_PortOutGet(gpioPortC), 0xf);	// Toggle LEDs
#endif

      puts("Tick...");
      fflush(stdout);
    }
  }
}
