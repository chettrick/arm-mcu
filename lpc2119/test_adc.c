/* Simple analog to digital converter test program */

// $Id: test_adc.c,v 1.7 2008-04-14 18:19:03 cvs Exp $

#include <conio.h>
#include <cpu.h>
#include <stdio.h>

#define MAX_ADC_CHANNELS	4
#define ADCSTART		0x01200D00
#define ADCDONE			0x80000000

#define STEPVOLTAGE	3.3/65536

unsigned int SampleADC(int channel)
{
  ADCR = ADCSTART + (1 << channel);	// Start conversion

  while (!(ADDR & ADCDONE));		// Wait until done

  return ADDR & 0xFFFF;
}

int main(void)
{
  int channel;
  int i;
  unsigned volatile char dummy;

  cpu_init(DEFAULT_CPU_FREQ);
  conio_init(0, 19200);

  puts("\033[H\033[2JLPC2119 A/D Converter Test (" __DATE__ " " __TIME__ ")\n");

  PINSEL1 = 0x15400000;			// Enable A/D inputs

  for (;;)
  {
    printf("\033[3;1H");

    for (channel = 0; channel < MAX_ADC_CHANNELS; channel++)
      printf("AIN%d is %5.3f V\n", channel, STEPVOLTAGE*SampleADC(channel));

    fflush(stdout);

    for (i = 0; i < 1000000; i++) dummy++;
  }
}
