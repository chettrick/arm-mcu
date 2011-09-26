/* Simple serial console I/O test program for the STM32 ARM MCU */

// $Id$

static const char revision[] = "$Id$";

#include <assert.h>
#include <cpu.h>
#include <errno.h>
#include <inet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <W5200.h>

#ifdef W5200E01_M3
#define SPIPORT		1
#define W5200_INT_PIN	GPIOPIN16
#define W5200_INT	GPIOPIN16IN
#define W5200_RESET_PIN	GPIOPIN24
#define W5200_RESET	GPIOPIN24OUT
#define W5200_PWDN_PIN	GPIOPIN25
#define W5200_PWDN	GPIOPIN25OUT
#endif

// SPI port configuration

#define SPICLOCKMODE	0
#define SPISPEED	281250
#define SPIENDIAN	SPI_BIGENDIAN

// Predefined addresses

const macaddress_t macaddress	= { 0x02, 0x00, 0x00, 0x00, 0x00, 0x01 };

static volatile uint32_t delaycounter = 0;

void SysTick_Handler(void)
{
  if (delaycounter)	// Decrement delay counter
    delaycounter--;

  W5200_tick();		// Call W5200 driver tick routine
}

void delay(uint32_t ticks)
{
  delaycounter = ticks;
  while (delaycounter);
}

int main(void)
{
  int status;
  macaddress_t macaddr;
  ipv4address_t ipaddr, subnet, gateway;
  char buf[256];
  int linkstate = FALSE;

  cpu_init(DEFAULT_CPU_FREQ);

  serial_stdio(CONSOLE_PORT, 115200);

  puts("\033[H\033[2JSTM32 WizNet W5200 Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", CPUFREQ, __VERSION__);

// Initialize System Tick with 10 ms time interval

  SysTick_Config(SystemCoreClock / 100);

// Configure GPIO pins

  gpiopin_configure(W5200_INT_PIN, GPIOPIN_INPUT);
  gpiopin_configure(W5200_RESET_PIN, GPIOPIN_OUTPUT);
  gpiopin_configure(W5200_PWDN_PIN, GPIOPIN_OUTPUT);

// Deassert PWDN

  W5200_PWDN = 0;
  delay(2);

// Assert nRST

  W5200_RESET = 0;
  delay(2);

// Deassert nRST

  W5200_RESET = 1;
  delay(20);

// Initialize SPI hardware

  if ((status = spimaster_init(SPIPORT, SPICLOCKMODE, SPISPEED, SPIENDIAN)))
  {
    fprintf(stderr, "ERROR: spimaster_init() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

// Initialize the W5200

  if ((status = W5200_initialize(SPIPORT)))
  {
    fprintf(stderr, "ERROR: W5200_initialize() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

  if ((status = W5200_set_hardware_address(macaddress)))
  {
    fprintf(stderr, "ERROR: W5200_set_hardware_address() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

  if ((status = W5200_get_hardware_address(macaddr)))
  {
    fprintf(stderr, "ERROR: W5200_get_hardware_address() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

  printf("W5200 MAC address is %02X:%02X:%02X:%02X:%02X:%02X\n",
    macaddr[0], macaddr[1], macaddr[2], macaddr[3], macaddr[4], macaddr[5]);

  if (inet_pton(AF_INET, "10.0.4.129", ipaddr) != 1)
  {
    fprintf(stderr, "ERROR: inet_pton() failed, %s\n", strerror(errno));
    assert(FALSE);
  }
  if (inet_pton(AF_INET, "255.255.255.0", subnet) != 1)
  {
    fprintf(stderr, "ERROR: inet_pton() failed, %s\n", strerror(errno));
    assert(FALSE);
  }
  if (inet_pton(AF_INET, "10.0.4.1", gateway) != 1)
  {
    fprintf(stderr, "ERROR: inet_pton() failed, %s\n", strerror(errno));
    assert(FALSE);
  }

  if ((status = W5200_configure_network(ipaddr, subnet, gateway)))
  {
    fprintf(stderr, "ERROR: W5200_configure_network() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

  if ((status = W5200_get_ipaddress(ipaddr)))
  {
    fprintf(stderr, "ERROR: W5200_get_ip_address() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

  if (inet_ntop(AF_INET, ipaddr, buf, sizeof(buf)))
  {
    fprintf(stderr, "ERROR: inet_ntop() failed, %s\n", strerror(errno));
    assert(FALSE);
  }

  printf("W5200 IP address is  %d.%d.%d.%d\n\n", ipaddr[0], ipaddr[1], ipaddr[2], ipaddr[3]);

  for (;;)
  {
    if ((status = W5200_get_linkstate(&linkstate)))
    {
      fprintf(stderr, "ERROR: W5200_get_linkstate() returned %d, %s\n", status, strerror(errno));
      assert(FALSE);
    }

    printf("Link state: %s\r", linkstate ? "YES" : "NO ");
  }
}
