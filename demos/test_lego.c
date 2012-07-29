/* LEGO Power Functions Remote Control test program */

// Reference "LEGO Power Functions RC Version 1.20"

// $Id: test_gpio.c 3199 2011-10-18 11:28:12Z svn $

static const char revision[] = "$Id: test_gpio.c 3199 2011-10-18 11:28:12Z svn $";

#include <cpu.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef FEZ_CERB40
#define LEDPIN		GPIOPIN32	// PC0
#define LEDOUT		GPIOPIN32OUT	// PC0
#define DELAY38KHZ	182
#endif

typedef enum
{
  BIT_LOW	= 0,
  BIT_HIGH	= 1,
  BIT_START	= 2,
  BIT_STOP	= 3,
} lego_bit_t;

const int LEGO_BIT_LOW_TIMES[] = { 10, 21, 39, 39 };  // Cycles of silence following the mark

static void SendBit(lego_bit_t bit)
{
  unsigned long int n, i, j;

// Send mark, 6 cycles of 38 kHz square wave

  n = 12;

  for (i = 1; i <= n; i++)
  {
    for (j = 0; j < DELAY38KHZ; j++);

    LEDOUT = i;
  }

// Send space, n cycles of silence

  n = 2*LEGO_BIT_LOW_TIMES[bit];

  for (i = 1; i <= n; i++)
  {
    for (j = 0; j < DELAY38KHZ; j++);

    LEDOUT = 0;
  }
}

static void SendFrame(uint16_t data)
{
  int i;
  uint8_t LRC;

  LRC = (0xF ^ ((data >> 8) & 0x0F) ^ ((data >> 4) & 0x0F) ^ (data & 0x0F)) & 0x0F;

  data <<= 4;
  data &= 0xFFF0;
  data |= LRC;

  SendBit(BIT_START);

  for (i = 0; i < 16; i++)
  {
    SendBit((data >> 15) & 0x01);

    data <<= 1;
  }

  SendBit(BIT_STOP);
}

#define SYSTICKRATE	50

_BEGIN_STD_C

volatile int TimerCounter = 0;
volatile uint16_t frame = 0x400;

void SysTick_Handler(void)
{
  if (++TimerCounter == SYSTICKRATE)
  {
    TimerCounter = 0;
    SendFrame(frame);
  }
}

_END_STD_C

int main(void)
{
  char inbuf[16];
  uint8_t __attribute__ ((aligned (4))) channel;
  uint8_t __attribute__ ((aligned (4))) SpeedB;
  uint8_t __attribute__ ((aligned (4))) SpeedA;
  uint16_t newframe;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef CONSOLE_USB
  usb_serial_stdio(NULL);
  getch();
#else
  serial_stdio(CONSOLE_PORT);
#endif

#ifdef INTERACTIVE
  printf("\033[H\033[2J%s LEGO Power Functions RC Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s %s %s\n\n", SystemCoreClock, __COMPILER__, __VERSION__, __ABI__);
#endif

// Initialize System Tick

  SysTick_Config(SystemCoreClock / SYSTICKRATE);

// Initialize the LED output

  gpiopin_configure(LEDPIN, GPIOPIN_OUTPUT);

  LEDOUT = 0;

// Get RC channel number

#ifdef INTERACTIVE
  do
  {
    printf("Enter channel number (1 to 4): ");
    fflush(stdout);
    memset(inbuf, 0, sizeof(inbuf));
    gets(inbuf);
    channel = atoi(inbuf) - 1;
  }
  while (channel > 3);
#endif

  for (;;)
  {

// Get motor speeds from operator

#ifdef INTERACTIVE
    do
    {
      printf("Enter motor speeds (0-F 0-F): ");
      fflush(stdout);
      memset(inbuf, 0, sizeof(inbuf));
      fflush(stdin);
      gets(inbuf);
      SpeedA = 0xFF;
      SpeedB = 0xFF;
      sscanf(inbuf, "%hhx %hhx", &SpeedA, &SpeedB);
    }
    while ((SpeedA > 15) || (SpeedB > 15));
#else
    do
    {
      memset(inbuf, 0, sizeof(inbuf));
      fflush(stdin);
      gets(inbuf);
      channel = 0xFF;
      SpeedA = 0xFF;
      SpeedB = 0xFF;
      sscanf(inbuf, "%hhu %hhu %hhu", &channel, &SpeedA, &SpeedB);
    }
    while ((channel > 3) || (SpeedA > 15) || (SpeedB > 15));
#endif

// Assemble new frame

    newframe = 0x400 | (channel << 8) | (SpeedB << 4) | SpeedA;

// Move new frame to staging area

    frame = newframe;
  }
}
