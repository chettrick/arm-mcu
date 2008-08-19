/* Simple serial console I/O test program */

// $Id: test_adc.c,v 1.1 2008-08-19 08:33:58 cvs Exp $

#include <cpu.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

unsigned short int SampleADC(int channel)
{
  ADC_InitTypeDef adcinit;

// Initalize A/D converter

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

#ifdef CONFIG_USBCONSOLE
  usb_serial_stdio();
  getch();
#else
  serial_stdio(0, 19200);
#endif

  puts("\033[H\033[2JSTR912FAW44 A/D Converter Test (" __DATE__ " " __TIME__ ")\n");

// Turn on peripheral clocks

  SCU_APBPeriphClockConfig(__RTC, ENABLE);
  SCU_APBPeriphClockConfig(__ADC, ENABLE);
  SCU_APBPeriphClockConfig(__GPIO4, ENABLE);

// Configure RTC

  RTC_DeInit();

// Initialize A/D input 6

  GPIO_DeInit(GPIO4);
  GPIO_ANAPinConfig(GPIO_ANAChannel6, ENABLE);

// Initialize A/D converter

  ADC_DeInit();
  ADC_Cmd(ENABLE);
  ADC_PrescalerConfig(0x2);

// Sample A/D input 6 once a second

  then = 0;

  for (;;)
  {
    now = time(NULL);
    if (now == then) continue;
    then = now;

    printf("The value of A/D input 6 is %04X\n", SampleADC(ADC_Channel_6));
  }
}
