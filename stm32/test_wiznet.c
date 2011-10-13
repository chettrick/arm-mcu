/* Simple serial console I/O test program for the STM32 ARM MCU */

// $Id$

static const char revision[] = "$Id$";

#ifndef WIZNET
#error You must define WIZNET to compile this application
#endif

#include <assert.h>
#include <cpu.h>
#include <errno.h>
#include <inet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiznet.h>

// WizNet configuration for STM32-P103 board with W5100 UEXT module

#ifdef OLIMEX_STM32_P103
#define WIZNET_SPIPORT		1
#define WIZNET_SPICLOCKMODE	0
#define WIZNET_SPISPEED		9000000
#define WIZNET_SPIENDIAN	SPI_BIGENDIAN
#define WIZNET_INT_PIN		GPIOPIN22
#define WIZNET_INT		GPIOPIN22IN
#define WIZNET_NRESET_PIN	GPIOPIN23
#define WIZNET_NRESET		GPIOPIN23OUT
#endif

// WizNet configuration for STM32-P107 board with W5100 UEXT module

#ifdef OLIMEX_STM32_P107
#define WIZNET_SPIPORT		1
#define WIZNET_SPICLOCKMODE	0
#define WIZNET_SPISPEED		9000000
#define WIZNET_SPIENDIAN	SPI_BIGENDIAN
#define WIZNET_INT_PIN		GPIOPIN24
#define WIZNET_INT		GPIOPIN24IN
#define WIZNET_NRESET_PIN	GPIOPIN25
#define WIZNET_NRESET		GPIOPIN25OUT
#endif

// WizNet configuration for W5200E01-M3 board

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

static volatile uint32_t delaycounter = 0;

void SysTick_Handler(void)
{
  if (delaycounter)	// Decrement delay counter
    delaycounter--;

  wiznet_tick();	// Call WizNet driver tick routine
}

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
  char buf[256];
#ifdef W5200
  uint32_t linkstate = FALSE;
#endif
  uint32_t count;
  ipv4address_t senderaddr;
  uint32_t senderport;
  char senderaddrbuf[256];

  cpu_init(DEFAULT_CPU_FREQ);

  serial_stdio(CONSOLE_PORT, 115200);

  puts("\033[H\033[2JSTM32 WizNet Network Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", CPUFREQ, __VERSION__);

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
    fprintf(stderr, "ERROR: spimaster_init() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

// Initialize the WizNet device

  if ((status = wiznet_initialize(WIZNET_SPIPORT, 8)))
  {
    fprintf(stderr, "ERROR: wiznet_initialize() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

  if ((status = wiznet_set_hardware_address(macaddress)))
  {
    fprintf(stderr, "ERROR: wiznet_set_hardware_address() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

  if ((status = wiznet_get_hardware_address(macaddr)))
  {
    fprintf(stderr, "ERROR: wiznet_get_hardware_address() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

  printf("\033[6;1HMAC address is %02X:%02X:%02X:%02X:%02X:%02X\n",
    macaddr[0], macaddr[1], macaddr[2], macaddr[3], macaddr[4], macaddr[5]);
  fflush(stdout);

  if (inet_pton(AF_INET, "10.0.5.100", ipaddr) != 1)
  {
    fprintf(stderr, "ERROR: inet_pton() failed, %s\n", strerror(errno));
    assert(FALSE);
  }

  if (inet_pton(AF_INET, "255.255.255.0", subnet) != 1)
  {
    fprintf(stderr, "ERROR: inet_pton() failed, %s\n", strerror(errno));
    assert(FALSE);
  }

  if (inet_pton(AF_INET, "10.0.5.1", gateway) != 1)
  {
    fprintf(stderr, "ERROR: inet_pton() failed, %s\n", strerror(errno));
    assert(FALSE);
  }

  if ((status = wiznet_configure_network(ipaddr, subnet, gateway)))
  {
    fprintf(stderr, "ERROR: wiznet_configure_network() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

  memset(ipaddr, 0, sizeof(ipaddr));

  if ((status = wiznet_get_ipaddress(ipaddr)))
  {
    fprintf(stderr, "ERROR: wiznet_get_ip_address() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

  if (inet_ntop(AF_INET, ipaddr, buf, sizeof(buf)) == NULL)
  {
    fprintf(stderr, "ERROR: inet_ntop() failed, %s\n", strerror(errno));
    assert(FALSE);
  }

  printf("IP address is %s\n", buf);
  fflush(stdout);

  wiznet_udp_open(0, 1234);

  for (;;)
  {
#ifdef W5200
    if ((status = wiznet_get_linkstate(&linkstate)))
    {
      fprintf(stderr, "ERROR: wiznet_get_linkstate() returned %d, %s\n", status, strerror(errno));
      assert(FALSE);
    }

    printf("\033[8;1HLink state: %s", linkstate ? "YES" : "NO ");
    fflush(stdout);
#endif

    if ((status = wiznet_get_receive_ready(0, &count)))
    {
      fprintf(stderr, "ERROR: wiznet_get_receive_ready() returned %d, %s\n", status, strerror(errno));
      assert(FALSE);
    }

    printf("\033[9;1HReceive bytes available: %-5lu", count);
    fflush(stdout);

    if (count)
    {
      if ((status = wiznet_udp_receive_from(0, senderaddr, &senderport, buf, &count)) && (errno != ENODATA))
      {
        fprintf(stderr, "ERROR: wiznet_udp_receive() returned %d, %s\n", status, strerror(errno));
        assert(FALSE);
      }

      memset(senderaddrbuf, 0, sizeof(senderaddrbuf));
      inet_ntop(AF_INET, senderaddr, senderaddrbuf, sizeof(senderaddrbuf));
      printf("\033[10;1HReceived %lu bytes from %s:%-5lu\n", count, senderaddrbuf, senderport);
    }

    delay(100);
  }
}
