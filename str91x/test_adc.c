/* Simple A/D converter test program for the STR91x ARM MCU */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

unsigned short int SampleADC(int channel)
{
  ADC_InitTypeDef adcinit;

// Set A/D channel and mode

  ADC_StructInit(&adcinit);
  adcinit.ADC_Channel_0_Mode = ADC_NoThreshold_Conversion;
  adcinit.ADC_Channel_1_Mode = ADC_NoThreshold_Conversion;
  adcinit.ADC_Channel_2_Mode = ADC_NoThreshold_Conversion;
  adcinit.ADC_Channel_3_Mode = ADC_NoThreshold_Conversion;
  adcinit.ADC_Channel_4_Mode = ADC_NoThreshold_Conversion;
  adcinit.ADC_Channel_5_Mode = ADC_NoThreshold_Conversion;
  adcinit.ADC_Channel_6_Mode = ADC_NoThreshold_Conversion;
  adcinit.ADC_Channel_7_Mode = ADC_NoThreshold_Conversion;
  adcinit.ADC_Select_Channel = channel;
  adcinit.ADC_Scan_Mode = DISABLE;
  adcinit.ADC_Conversion_Mode = ADC_Single_Mode;
  ADC_Init(&adcinit);

// Start A/D conversion

  ADC_ConversionCmd(ADC_Conversion_Start);
  while (!ADC_GetFlagStatus(ADC_FLAG_ECV));

// Read result

  return ADC_GetConversionValue(channel);
}

int main(void)
{
  time_t then, now;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef CONSOLE_USB
  usb_serial_stdio(NULL);
  getch();
#else
  serial_stdio(CONSOLE_PORT);
#endif

  puts("\033[H\033[2JSTR91x A/D Converter Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s %s %s\n\n", CPUFREQ, __COMPILER__, __VERSION__, __ABI__);

// Turn on peripheral clocks

  SCU_APBPeriphClockConfig(__RTC, ENABLE);
  SCU_APBPeriphClockConfig(__ADC, ENABLE);
  SCU_APBPeriphClockConfig(__GPIO4, ENABLE);

// Configure RTC

  RTC_DeInit();			// Reset RTC

// Configure P4.6 as analog input 6

  GPIO_DeInit(GPIO4);		// Reset GPIO4
  GPIO_ANAPinConfig(GPIO_ANAChannel6, ENABLE);

// Configure A/D converter

  ADC_DeInit();			// Reset A/D converter
  ADC_Cmd(ENABLE);		// Power on A/D converter
  ADC_PrescalerConfig(0x2);	// Conversion clock is 24 MHz

// Sample analog input 6 once a second

  then = 0;

  for (;;)
  {
    now = time(NULL);
    if (now == then) continue;
    then = now;

    printf("The value of A/D input 6 is %04X\n", SampleADC(ADC_Channel_6));
  }
}
