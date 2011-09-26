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

// SPI port configuration

#define SPIPORT		1
#define SPICLOCKMODE	0
#define SPISPEED	281250
#define SPIENDIAN	TRUE

// Predefined addresses

const macaddress_t macaddress	= { 0x02, 0x00, 0x00, 0x00, 0x00, 0x01 };
const ipv4address_t ipaddress	= { 10, 0, 4, 129 };
const ipv4address_t subnet	= { 255, 255, 255, 0 };
const ipv4address_t gateway	= { 10, 0, 4, 1 };

void SysTick_Handler(void)
{
  W5200_tick();
}

int main(void)
{
  int status;
  uint8_t buf[256];
  int linkstate = FALSE;

  cpu_init(DEFAULT_CPU_FREQ);

  serial_stdio(CONSOLE_PORT, 115200);

  puts("\033[H\033[2JSTM32 WizNet W5200 Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", CPUFREQ, __VERSION__);

// Initialize System Tick with 10 ms time interval

  SysTick_Config(SystemCoreClock / 100);

// Initialize SPI hardware

  if ((status = spimaster_init(SPIPORT, SPICLOCKMODE, SPISPEED, SPIENDIAN)))
  {
    fprintf(stderr, "ERROR: spimaster_init() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

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

  if ((status = W5200_get_hardware_address(buf)))
  {
    fprintf(stderr, "ERROR: W5200_get_hardware_address() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

  printf("W5200 MAC address is %02X:%02X:%02X:%02X:%02X:%02X\n",
    buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);

  if ((status = W5200_configure_network(ipaddress, subnet, gateway)))
  {
    fprintf(stderr, "ERROR: W5200_configure_network() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

  if ((status = W5200_get_ipaddress(buf)))
  {
    fprintf(stderr, "ERROR: W5200_get_ip_address() returned %d, %s\n", status, strerror(errno));
    assert(FALSE);
  }

  printf("W5200 IP address is  %d.%d.%d.%d\n\n", buf[0], buf[1], buf[2], buf[3]);

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
