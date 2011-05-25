/* Simple FreeRTOS test program for the LPC1768 ARM MCU */

// $Id$

static const char revision[] = "$Id$";

#ifndef FREERTOS
#error You must define FREERTOS to compile this FreeRTOS application
#endif

#include <assert.h>
#include <cpu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <FreeRTOS.h>
#include <task.h>

void TaskFunction(void *parameters)
{
  char *message = parameters;
  unsigned int seed = (unsigned int) &seed;

  portTickType waketime = xTaskGetTickCount();

  for (;;)
  {
    cputs(message);
    vTaskDelayUntil(&waketime, (1000 + (rand_r(&seed) % 500))/portTICK_RATE_MS);    
  }
}

int main(void)
{
  xTaskHandle task1;

  cpu_init(DEFAULT_CPU_FREQ);

  serial_stdio(CONSOLE_PORT, 115200);

  puts("\033[H\033[2JLPC1768 FreeRTOS Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s  FreeRTOS:%s\n\n", CPUFREQ, __VERSION__,
    tskKERNEL_VERSION_NUMBER);

  if (xTaskCreate(TaskFunction, (signed char *) "Task 1", 240, "This is Task 1\r\n", 1, &task1) != pdPASS)
  {
    puts("ERROR: xTaskCreate() for task 1 failed!");
    fflush(stdout);
    assert(0);
  }

  if (xTaskCreate(TaskFunction, (signed char *) "Task 2", 240, "This is Task 2\r\n", 1, &task1) != pdPASS)
  {
    puts("ERROR: xTaskCreate() for task 2 failed!");
    fflush(stdout);
    assert(0);
  }

  vTaskStartScheduler();
  assert(0);
}

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
  printf("ERROR: vApplicationStackOverflowHook(): Task \"%s\" overflowed its stack\n", pcTaskName);
  fflush(stdout);
  assert(0);
}
