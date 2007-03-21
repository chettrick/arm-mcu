/* Simple analog to digital converter test program */

// $Id: test_adc.c,v 1.2 2007-03-21 23:34:51 cvs Exp $

#include <lpc2119/conio.h>
#include <lpc2119/io.h>

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

  MAMCR = 2;			// MAM functions fully enabled

  VPBDIV = 0x01;		// pclk = cclk

  PLLCFG = (0x01 << 5) + 0x02;	// M=3, P=2
  PLLCON = 1;
  PLLFEED = 0xAA;
  PLLFEED = 0x55;
  while((PLLSTAT & 0x400) == 0);
  PLLCON = 3;
  PLLFEED = 0xAA;
  PLLFEED = 0x55;

  conio_init(19200);

  puts("\033[H\033[2JLPC2119 A/D Converter Test\n");

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
