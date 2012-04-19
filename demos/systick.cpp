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

class test
{
public:

  test(unsigned int d)
  {
    this->param = d;
  }

  unsigned int param;
};

class tost
{
public:

  tost(unsigned int e)
  {
    this->param = e;
  }

  unsigned int param;
};

// Create a global object

test mytest1 = test(1);

test mytest3(3);

tost mytest4(4);

tost mytest5 = tost(5);

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);

  serial_stdio(CONSOLE_PORT);

  printf("\033[H\033[2J%s System Tick Interrupt Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s %s %s\n\n", CPUFREQ, __COMPILER__, __VERSION__, __ABI__);

// Create a local object

  test mytest2(2);

// Test the objects

  if (mytest1.param == 1)
  {
    puts("Object mytest1 was created successfully!\n");
  }

  if (mytest2.param == 2)
  {
    puts("Object mytest2 was created successfully!\n");
  }

  if (mytest3.param == 3)
  {
    puts("Object mytest3 was created successfully!\n");
  }

  if (mytest4.param == 4)
  {
    puts("Object mytest4 was created successfully!\n");
  }

  if (mytest5.param == 5)
  {
    puts("Object mytest3 was created successfully!\n");
  }

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
