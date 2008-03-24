/******************************************************************************/
/*                                                                            */
/*      Simple serial console I/O routines for the STR912FAW44 ARM MCU        */
/*                                                                            */
/******************************************************************************/

// $Id: conio.c,v 1.3 2008-03-24 11:17:21 cvs Exp $

#include <conio.h>
#include <cpu.h>
#include <stdio.h>
#include <string.h>

static USART_TypeDef *UART = (USART_TypeDef *) USART1_BASE;

/* Initialize serial console */

void conio_init(unsigned port, unsigned long int baudrate)
{
  USART_InitTypeDef USART_config;
  GPIO_InitTypeDef GPIO_config;
  
// Turn on USART

  switch (port)
  {
    case 1 :
      UART = (USART_TypeDef *) USART1_BASE;

// Turn on peripheral clocks

      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

// Configure TX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_9;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA, &GPIO_config);

// Configure RX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_10;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      GPIO_Init(GPIOA, &GPIO_config);
      break;
 
    case 2 :
      UART = (USART_TypeDef *) USART2_BASE;

// Turn on peripheral clocks

      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

// Configure TX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_2;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA, &GPIO_config);

// Configure RX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_3;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      GPIO_Init(GPIOA, &GPIO_config);
      break;
 
    case 3 :
      UART = (USART_TypeDef *) USART3_BASE;

// Turn on peripheral clocks

      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

// Configure TX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_10;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA, &GPIO_config);

// Configure RX pin

      GPIO_config.GPIO_Pin = GPIO_Pin_11;
      GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_config.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      GPIO_Init(GPIOB, &GPIO_config);
      break;
  }

// Configure USART

  USART_StructInit(&USART_config);
  USART_config.USART_BaudRate = baudrate;
  USART_Init(UART, &USART_config);
  USART_Cmd(UART, ENABLE);
}

/* Send 1 character */

void putch(unsigned char c)
{
  if (c == '\n') putch('\r');

  while (!(UART->SR & USART_FLAG_TXE));
  UART->DR = c;
}

/* Receive 1 character */

unsigned char getch(void)
{
  while (!(UART->SR & USART_FLAG_RXNE));
  return UART->DR;
}

/* Return 1 if key pressed */

unsigned char keypressed(void)
{
  return (UART->SR & USART_FLAG_RXNE);
}

/* Send a string */

void cputs(char *s)
{
  while (*s)
    putch(*s++);
}

/* Receive a string, with rudimentary line editing */

void cgets(char *s, int bufsize)
{
  char *p;
  int c;

  memset(s, 0, bufsize);

  p = s;

  for (p = s; p < s + bufsize-1;)
  {
    c = getch();
    switch (c)
    {
      case '\r' :
      case '\n' :
        putch('\r');
        putch('\n');
        *p = '\n';
        return;

      case '\b' :
        if (p > s)
        {
          *p-- = 0;
          putch('\b');
          putch(' ');
          putch('\b');
        }
        break;

      default :
        putch(c);
        *p++ = c;
        break;
    }
  }

  return;
}

/* Override fgets() with a version that does line editing */

char *fgets(char *s, int bufsize, FILE *f)
{
  cgets(s, bufsize);
  return s;
}
