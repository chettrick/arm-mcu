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

  puts("\033[H\033[2JLPC1768 System Tick Interrupt Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", CPUFREQ, __VERSION__);

// Initialize LED(s)

#ifdef BOARD_MBED_LPC1768
#define LED1	18
#define LED2	20
#define LED3	21
#define LED4	23

#define LEDMASK	((1 << LED1)|(1 << LED2)|(1 << LED3)|(1 << LED4))

  LPC_GPIO1->FIOMASK &= ~LEDMASK;
  LPC_GPIO1->FIODIR |= LEDMASK;
  LPC_GPIO1->FIOPIN = (1 << LED1)|(0 << LED2)|(1 << LED3)|(0 <<LED4);
#endif

#ifdef BOARD_BLUEBOARD_LPC1768_H
#define LED1	29

#define LEDMASK	((1 << LED1))

  LPC_GPIO1->FIOMASK &= ~LEDMASK;
  LPC_GPIO1->FIODIR |= LEDMASK;
  LPC_GPIO1->FIOPIN = (1 << LED1);
#endif

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

#ifdef BOARD_MBED_LPC1768
      LPC_GPIO1->FIOPIN = ~LPC_GPIO1->FIOPIN;	// Toggle LEDs
#endif

#ifdef BOARD_BLUEBOARD_LPC1768_H
      LPC_GPIO1->FIOPIN = ~LPC_GPIO1->FIOPIN;	// Toggle LED
#endif
    }
  }
}
