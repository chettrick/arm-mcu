/* Simple FreeRTOS test program */

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
#include <semphr.h>
#include <task.h>

#ifdef CONSOLE_CONIO
#error This program cannot use the lightweight console I/O library
#endif

#define MESSAGE_PERIOD	4000

xSemaphoreHandle console_lock;

void putsTaskFunction(void *parameters)
{
  portTickType waketime = xTaskGetTickCount();

  for (;;)
  {
    vTaskDelayUntil(&waketime, (MESSAGE_PERIOD/2 + (lrand48() % (MESSAGE_PERIOD/2)))/portTICK_RATE_MS);

    xSemaphoreTake(console_lock, portMAX_DELAY);
    printf("This is %s\n", pcTaskGetTaskName(NULL));
    xSemaphoreGive(console_lock);
  }
}

void LEDTaskFunction(void *parameters)
{
  portTickType waketime = xTaskGetTickCount();

// Configure LED(s)

  LEDS_initialize();
  LEDS_set(LED2|LED3|LED6|LED7);

  for (;;)
  {
    vTaskDelayUntil(&waketime, 1000/portTICK_RATE_MS);

// Toggle LED(s)

    LEDS_set(~LEDS_get());
  }
}

int main(void)
{
  xTaskHandle task1;
  xTaskHandle task2;
  xTaskHandle task3;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef CONSOLE_USB
  usb_serial_stdio(NULL);
  getch();
#else
  serial_stdio(CONSOLE_PORT);
#endif

// Display version information

  printf("\033[H\033[2J%s FreeRTOS Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  puts(revision);
  printf("\nCPU Freq:%u Hz  Compiler:%s %s %s  FreeRTOS:%s\n\n", (unsigned int) SystemCoreClock,
    __COMPILER__, __VERSION__, __ABI__, tskKERNEL_VERSION_NUMBER);

// Create mutex to arbitrate console output

  console_lock = xSemaphoreCreateMutex();
  if (console_lock == NULL)
  {
    puts("ERROR: xSemaphoreCreateMutex() for console_lock failed!");
    fflush(stdout);
    assert(FALSE);
  }

// Create a couple of tasks

  if (xTaskCreate(putsTaskFunction, (signed char *) "task1", 512, NULL, 1, &task1) != pdPASS)
  {
    puts("ERROR: xTaskCreate() for task1 failed!");
    fflush(stdout);
    assert(FALSE);
  }

  if (xTaskCreate(putsTaskFunction, (signed char *) "task2", 512, NULL, 1, &task2) != pdPASS)
  {
    puts("ERROR: xTaskCreate() for task2 failed!");
    fflush(stdout);
    assert(FALSE);
  }

  if (xTaskCreate(LEDTaskFunction, (signed char *) "task3", 256, NULL, 1, &task3) != pdPASS)
  {
    puts("ERROR: xTaskCreate() for task3 failed!");
    fflush(stdout);
    assert(FALSE);
  }

  vTaskStartScheduler();
  assert(FALSE);
}

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
  printf("ERROR: vApplicationStackOverflowHook(): Task \"%s\" overflowed its stack\n", pcTaskName);
  fflush(stdout);
  assert(FALSE);
}
