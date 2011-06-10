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

  puts("\033[H\033[2JSTM32 System Tick Interrupt Test ("
       __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", CPUFREQ, __VERSION__);

// Initialize System Tick with 100ms time interval

  SysTick_Config(SystemCoreClock / 10);

#ifdef OLIMEX_STM32_P103
// Enable GPIOC peripheral clock

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);

// Configure PC.12 as output push-pull (LED)

  GPIO_InitTypeDef config;

  GPIO_StructInit(&config);
  config.GPIO_Pin =  GPIO_Pin_12;
  config.GPIO_Mode = GPIO_Mode_Out_PP;
  config.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &config);

// Turn LED off

  GPIO_SetBits(GPIOC, GPIO_Pin_12);
#endif

#ifdef STM32_VALUE_LINE_DISCOVERY
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

#ifdef OLIMEX_STM32_P103
      GPIO_WriteBit(GPIOC, GPIO_Pin_12, !GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_12));
#endif

#ifdef STM32_VALUE_LINE_DISCOVERY
      GPIO_WriteBit(GPIOC, GPIO_Pin_9, !GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_9));
#endif
    }
  }
}
