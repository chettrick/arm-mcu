/* Simple timer interrupt test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <stdio.h>

#define TRUE	1
#define	FALSE	0

volatile int TimerCounter = 0;
volatile int TimerFlag = FALSE;

void SysTickHandler(void)
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

  puts("\033[H\033[2JSTM32F103 System Tick Interrupt Test ("
       __DATE__ " " __TIME__ ")\n");

// Interrupt vectors are in flash

  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

// Initialize System Tick with 100ms time interval

  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
  SysTick_SetReload(900000);
  SysTick_CounterCmd(SysTick_Counter_Clear);
  SysTick_CounterCmd(SysTick_Counter_Enable);
  SysTick_ITConfig(ENABLE);

// Display "Tick..." every second

  for (;;)
  {
    if (TimerFlag)
    {
      TimerFlag = FALSE;
      puts("Tick...");
      fflush(stdout);
    }
  }
}
