/* Simple timer interrupt test program */

// $Id: test_systick.c 2650 2011-05-19 16:40:47Z svn $

static const char revision[] = "$Id: test_systick.c 2650 2011-05-19 16:40:47Z svn $";

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

  puts("\033[H\033[2JSTM32F100 System Tick Interrupt Test ("
       __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", CPUFREQ, __VERSION__);

// Interrupt vectors are in flash

  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

// Initialize System Tick with 100ms time interval

  SysTick_Config(SystemCoreClock / 10);

#ifdef BOARD_STM32_VALUE_LINE_DISCOVERY
// Enable GPIOC peripheral clock

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);

// Configure PC.9 as output push-pull (LED)

  GPIO_InitTypeDef config;

  GPIO_StructInit(&config);
  config.GPIO_Pin =  GPIO_Pin_9;
  config.GPIO_Mode = GPIO_Mode_Out_PP;
  config.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &config);

// Turn LED off

  GPIO_SetBits(GPIOC, GPIO_Pin_9);
#endif

// Display "Tick..." every second

  for (;;)
  {
    if (TimerFlag)
    {
      TimerFlag = FALSE;
      puts("Tick...");
      fflush(stdout);

#ifdef BOARD_STM32_VALUE_LINE_DISCOVERY
      GPIO_WriteBit(GPIOC, GPIO_Pin_9, !GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_9));
#endif
    }
  }
}
