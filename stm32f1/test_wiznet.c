/* Simple serial console I/O test program for the STM32F1 ARM MCU */

// $Id$

static const char revision[] = "$Id$";

#ifndef WIZNET
#error You must define WIZNET to compile this application
#endif

#include <cpu.h>
#include <errno.h>
#include <inet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiznet.h>

#ifdef CONSOLE_CONIO
#error This program cannot use the lightweight console I/O library
#endif

// Hardware configuration for W5200E01-M3 board

#ifdef W5200E01_M3
#define WIZNET_SPIPORT		1
#define WIZNET_SPICLOCKMODE	0
#define WIZNET_SPISPEED		18000000
#define WIZNET_SPIENDIAN	SPI_BIGENDIAN
#define WIZNET_INT_PIN		GPIOPIN16
#define WIZNET_INT		GPIOPIN16IN
#define WIZNET_NRESET_PIN	GPIOPIN24
#define WIZNET_NRESET		GPIOPIN24OUT
#define WIZNET_PWDN_PIN		GPIOPIN25
#define WIZNET_PWDN		GPIOPIN25OUT
#endif

// Predefined addresses

const macaddress_t macaddress	= { 0x02, 0x00, 0x00, 0x00, 0x00, 0x01 };

_BEGIN_STD_C

static volatile uint32_t delaycounter = 0;

void SysTick_Handler(void)
{
  if (delaycounter)	// Decrement delay counter
    delaycounter--;

  wiznet_tick();	// Call WizNet driver tick routine
}

_END_STD_C

void delay(uint32_t milliseconds)
{
  delaycounter = milliseconds/10;
  while (delaycounter);
}

int main(void)
{
  int status;
  macaddress_t macaddr;
  ipv4address_t ipaddr, subnet, gateway;
  uint32_t linkstate = FALSE;
  size_t count;
  ipv4address_t senderaddr;
  uint16_t senderport;
  char ipaddrbuf[256];
  uint8_t udpdgbuf[2048];
  int i;

  cpu_init(DEFAULT_CPU_FREQ);

  serial_stdio(CONSOLE_PORT);

  puts("\033[H\033[2JSTM32F1 WizNet Network Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%u Hz  Compiler:%s %s %s\n\n", (unsigned int) SystemCoreClock,
    __COMPILER__, __VERSION__, __ABI__);

// Initialize System Tick with 10 ms time interval

  SysTick_Config(SystemCoreClock / 100);

// Configure GPIO pins

#ifdef WIZNET_INT
  gpiopin_configure(WIZNET_INT_PIN, GPIOPIN_INPUT);
#endif

#ifdef WIZNET_NRESET
  gpiopin_configure(WIZNET_NRESET_PIN, GPIOPIN_OUTPUT);
#endif

#ifdef WIZNET_PWDN
  gpiopin_configure(WIZNET_PWDN_PIN, GPIOPIN_OUTPUT);
#endif

#ifdef WIZNET_PWDN
// Deassert PWDN

  WIZNET_PWDN = 0;
  delay(20);
#endif

#ifdef WIZNET_NRESET
// Assert nRST

  WIZNET_NRESET = 0;
  delay(20);

// Deassert nRST

  WIZNET_NRESET = 1;
#endif

// Wait for WizNet reset to complete

  delay(200);

// Initialize SPI hardware

  if ((status = spimaster_init(WIZNET_SPIPORT, WIZNET_SPICLOCKMODE, WIZNET_SPISPEED, WIZNET_SPIENDIAN)))
  {
    printf("ERROR: spimaster_init() returned %d, %s\n", status, strerror(errno));
    exit(1);
  }

// Initialize the WizNet device

  if ((status = wiznet_initialize(WIZNET_SPIPORT, 4)))
  {
    printf("ERROR: wiznet_initialize() returned %d, %s\n", status, strerror(errno));
    exit(1);
  }

  if ((status = wiznet_set_hardware_address(macaddress)))
  {
    printf("ERROR: wiznet_set_hardware_address() returned %d, %s\n", status, strerror(errno));
    exit(1);
  }

  if ((status = wiznet_get_hardware_address(macaddr)))
  {
    printf("ERROR: wiznet_get_hardware_address() returned %d, %s\n", status, strerror(errno));
    exit(1);
  }

  printf("\033[6;1HMAC address is %02X:%02X:%02X:%02X:%02X:%02X\n",
    macaddr[0], macaddr[1], macaddr[2], macaddr[3], macaddr[4], macaddr[5]);

  if (inet_pton(AF_INET, "10.0.0.100", ipaddr) != 1)
  {
    printf("ERROR: inet_pton() failed, %s\n", strerror(errno));
    exit(1);
  }

  if (inet_pton(AF_INET, "255.255.255.0", subnet) != 1)
  {
    printf("ERROR: inet_pton() failed, %s\n", strerror(errno));
    exit(1);
  }

  if (inet_pton(AF_INET, "10.0.0.1", gateway) != 1)
  {
    printf("ERROR: inet_pton() failed, %s\n", strerror(errno));
    exit(1);
  }

  if ((status = wiznet_configure_network(ipaddr, subnet, gateway)))
  {
    printf("ERROR: wiznet_configure_network() returned %d, %s\n", status, strerror(errno));
    exit(1);
  }

  memset(ipaddr, 0, sizeof(ipaddr));

  if ((status = wiznet_get_ipaddress(ipaddr)))
  {
    printf("ERROR: wiznet_get_ip_address() returned %d, %s\n", status, strerror(errno));
    exit(1);
  }

  if (inet_ntop(AF_INET, ipaddr, ipaddrbuf, sizeof(ipaddrbuf)) == NULL)
  {
    printf("ERROR: inet_ntop() failed, %s\n", strerror(errno));
    exit(1);
  }

  printf("IP address is %s\n", ipaddrbuf);

  wiznet_udp_open(0, 1234);

  for (;;)
  {
    if ((status = wiznet_get_linkstate(&linkstate)))
    {
      printf("ERROR: wiznet_get_linkstate() returned %d, %s\n", status, strerror(errno));
      exit(1);
    }

    printf("\033[8;1HLink state: %s", linkstate ? "YES" : "NO ");

    if ((status = wiznet_get_receive_ready(0, &count)))
    {
      printf("ERROR: wiznet_get_receive_ready() returned %d, %s\n", status, strerror(errno));
      exit(1);
    }

    printf("\033[9;1HReceive bytes available: %-5u", (unsigned) count);

    if (count)
    {
      do
      {
        status = wiznet_udp_receive_from(0, senderaddr, &senderport, udpdgbuf, &count);
      }
      while (status && ((errno == ENODATA) || (errno == EBUSY)));

      if (status)
      {
        printf("ERROR: wiznet_udp_receive_from() returned %d, %s\n", status, strerror(errno));
        exit(1);
      }

      memset(ipaddrbuf, 0, sizeof(ipaddrbuf));
      inet_ntop(AF_INET, senderaddr, ipaddrbuf, sizeof(ipaddrbuf));
      printf("\033[10;1HReceived %u bytes from %s:%-5u\n", (unsigned) count, ipaddrbuf, senderport);

      for (i = 0; i < count; i++)
        udpdgbuf[i] = count - i;

      do
      {
        status = wiznet_udp_send_to(0, senderaddr, senderport, udpdgbuf, count);
      }
      while (status && ((errno == ENOBUFS) || (errno == EBUSY)));

      if (status)
      {
        printf("ERROR: wiznet_udp_send_to() returned %d, %s\n", status, strerror(errno));
        exit(1);
      }
    }

    delay(100);
  }
}
