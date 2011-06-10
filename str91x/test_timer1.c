/* Simple timer interrupt test program for the STR91x ARM MCU */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <stdio.h>

volatile int Timer1Flag = FALSE;

__attribute__ ((__interrupt__)) void TIM1_IRQHandler(void)
{
  static int ticks = 0;

  if (++ticks == 10)
  {
    ticks = 0;
    Timer1Flag = TRUE;
  }

  TIM1->SR = 0x0000;		// Clear OCF1
  TIM1->CNTR = 0x0000;		// Reset counter
  VIC0->VAR = 0;		// Signal end of interrupt
}

int main(void)
{
  TIM_InitTypeDef config_timer;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef CONSOLE_USB
  usb_serial_stdio();
  getch();
#else
  serial_stdio(CONSOLE_PORT, 115200);
#endif

  puts("\033[H\033[2JSTR91FAW44 Timer 1 Interrupt Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", CPUFREQ, __VERSION__);

/* Configure VIC */

  SCU_AHBPeriphClockConfig(__VIC, ENABLE);	// Enable VIC clock
  SCU_AHBPeriphReset(__VIC, DISABLE);		// Let VIC out of reset

/* Configure timer 1 to interrupt 10 times a second */

  SCU_APBPeriphClockConfig(__TIM01, ENABLE);	// Turn on timer 1 clock
  SCU_APBPeriphReset(__TIM01, DISABLE);		// Let timer 1 out of reset

  TIM_StructInit(&config_timer);
  config_timer.TIM_Mode = TIM_OCM_CHANNEL_1;
  config_timer.TIM_OC1_Modes = TIM_TIMING;
  config_timer.TIM_Clock_Source = TIM_CLK_APB;
  config_timer.TIM_Prescaler = 0xFF;
  config_timer.TIM_Pulse_Length_1 = CPUFREQ/256/5;
  TIM_Init(TIM1, &config_timer);
  TIM_CounterCmd(TIM1, TIM_CLEAR);
  TIM_ITConfig(TIM1, TIM_IT_OC1, ENABLE);
  TIM_CounterCmd(TIM1, TIM_START);

/* Configure timer 1 interrupt */

  DISABLE_INTERRUPTS(IRQ);

  VIC_Config(TIM1_ITLine, VIC_IRQ, 0);		// Configure timer 1 interrupt
  VIC_ITCmd(TIM1_ITLine, ENABLE);		// Enable timer 1 interrupt

  ENABLE_INTERRUPTS(IRQ);

#ifdef STMICRO_STR910_EVAL
  GPIO_InitTypeDef config;

  SCU_APBPeriphClockConfig(__GPIO9, ENABLE);    // Turn on GPIO9 clock
  SCU_APBPeriphReset(__GPIO9, DISABLE);         // Let GPIO9 out of reset

  GPIO_StructInit(&config);
  config.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  config.GPIO_Direction = GPIO_PinOutput;       // LED pins are outputs
  config.GPIO_Type = GPIO_Type_PushPull;        // LED pins are push pull outputs
  config.GPIO_Alternate = GPIO_OutputAlt1;      // LED pins are GPIO outputs
  GPIO_Init(GPIO9, &config);

  GPIO_Write(GPIO9, 0x05);			// Turn off LED's
#endif

/* Trivial main loop */

  for (;;)
    if (Timer1Flag)
    {
      Timer1Flag = FALSE;
      puts("Tick...");
      fflush(stdout);

#ifdef STMICRO_STR910_EVAL
      GPIO_Write(GPIO9, ~GPIO_Read(GPIO9));
#endif
    }
}
