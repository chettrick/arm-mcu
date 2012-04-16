/* Simple timer interrupt test program for the STR91x ARM MCU */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <stdio.h>

volatile int TimerFlag = FALSE;

_BEGIN_STD_C

__attribute__ ((__interrupt__)) void TIM1_IRQHandler(void)
{
  static int ticks = 0;

  if (++ticks == 10)
  {
    ticks = 0;
    TimerFlag = TRUE;
  }

  TIM1->SR = 0x0000;		// Clear OCF1
  TIM1->CNTR = 0x0000;		// Reset counter
  VIC0->VAR = 0;		// Signal end of interrupt
}

_END_STD_C

int main(void)
{
  TIM_InitTypeDef config_timer;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef CONSOLE_USB
  usb_serial_stdio(NULL);
  getch();
#else
  serial_stdio(CONSOLE_PORT);
#endif

  puts("\033[H\033[2JSTR91FAW44 Timer Interrupt Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s %s %s\n\n", CPUFREQ, __COMPILER__, __VERSION__, __ABI__);

/* Configure LED(s) */

  LEDS_initialize();
  LEDS_set(LED2|LED4|LED6|LED8);

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

/* Trivial main loop */

  for (;;)
  {
    if (TimerFlag)
    {
      TimerFlag = FALSE;
      puts("Tick...");
      fflush(stdout);

      LEDS_set(~LEDS_get());			// Toggle LED(s)
    }
  }
}
