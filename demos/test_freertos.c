/* Simple FreeRTOS test program */

// $Id$

// Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

static const char revision[] = "$Id$";

#ifdef CONIO_STDIO
#error This program cannot use the lightweight console I/O library
#endif

#ifndef FREERTOS
#error You must define FREERTOS to compile this FreeRTOS application
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cpu.h>

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

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

#ifdef CONSOLE_SERIAL
  serial_stdio(CONSOLE_PORT);
#endif

#ifdef CONSOLE_SEMIHOSTING
  semihosting_stdio(CONSOLE_PORT)
#endif

#ifdef CONSOLE_USB
  usb_serial_stdio(NULL);
  getch();
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
    assert(false);
  }

// Create a couple of tasks

  if (xTaskCreate(putsTaskFunction, (signed char *) "task1", 512, NULL, 1, &task1) != pdPASS)
  {
    puts("ERROR: xTaskCreate() for task1 failed!");
    fflush(stdout);
    assert(false);
  }

  if (xTaskCreate(putsTaskFunction, (signed char *) "task2", 512, NULL, 1, &task2) != pdPASS)
  {
    puts("ERROR: xTaskCreate() for task2 failed!");
    fflush(stdout);
    assert(false);
  }

  if (xTaskCreate(LEDTaskFunction, (signed char *) "task3", 256, NULL, 1, &task3) != pdPASS)
  {
    puts("ERROR: xTaskCreate() for task3 failed!");
    fflush(stdout);
    assert(false);
  }

  vTaskStartScheduler();
  assert(false);
}

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
  printf("ERROR: vApplicationStackOverflowHook(): Task \"%s\" overflowed its stack\n", pcTaskName);
  fflush(stdout);
  assert(false);
}
