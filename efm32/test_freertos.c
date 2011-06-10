/* Simple FreeRTOS test program for the EFM32 ARM MCU */

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

#define MESSAGE_PERIOD	4000

xSemaphoreHandle console_lock;

void putsTaskFunction(void *parameters)
{
  char *message = parameters;

  portTickType waketime = xTaskGetTickCount();

  for (;;)
  {
    vTaskDelayUntil(&waketime, (MESSAGE_PERIOD/2 + (lrand48() % (MESSAGE_PERIOD/2)))/portTICK_RATE_MS);

    xSemaphoreTake(console_lock, portMAX_DELAY);
    puts(message);
    xSemaphoreGive(console_lock);
  }
}

void LEDTaskFunction(void *parameters)
{
  portTickType waketime = xTaskGetTickCount();

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

  for (;;)
  {
    vTaskDelayUntil(&waketime, 1000/portTICK_RATE_MS);

// Toggle LED(s)

#ifdef EFM32_G8XX_STK
    GPIO_PortOutSetVal(gpioPortC, ~GPIO_PortOutGet(gpioPortC), 0xf);
#endif
  }
}

int main(void)
{
  xTaskHandle task1;
  xTaskHandle task2;
  xTaskHandle task3;

  cpu_init(DEFAULT_CPU_FREQ);

  serial_stdio(CONSOLE_PORT, 115200);

// Display version information

  puts("\033[H\033[2JEFM32 FreeRTOS Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s  FreeRTOS:%s\n\n", CPUFREQ, __VERSION__,
    tskKERNEL_VERSION_NUMBER);

// Create mutex to arbitrate console output

  console_lock = xSemaphoreCreateMutex();
  if (console_lock == NULL)
  {
    puts("ERROR: xSemaphoreCreateMutex() for console_lock failed!");
    fflush(stdout);
    assert(0);
  }

// Create a couple of tasks

  if (xTaskCreate(putsTaskFunction, (signed char *) "task1", 256, "This is Task 1", 1, &task1) != pdPASS)
  {
    puts("ERROR: xTaskCreate() for task1 failed!");
    fflush(stdout);
    assert(0);
  }

  if (xTaskCreate(putsTaskFunction, (signed char *) "task2", 256, "This is Task 2", 1, &task2) != pdPASS)
  {
    puts("ERROR: xTaskCreate() for task2 failed!");
    fflush(stdout);
    assert(0);
  }

  if (xTaskCreate(LEDTaskFunction, (signed char *) "task3", 256, NULL, 1, &task3) != pdPASS)
  {
    puts("ERROR: xTaskCreate() for task3 failed!");
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
