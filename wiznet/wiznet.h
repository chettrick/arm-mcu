/* WizNet Driver Function Prototypes */

// $Id$

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

typedef uint8_t macaddress_t[6];		// Ethernet MAC address

typedef uint8_t ipv4address_t[4];		// IPv4 address

void wiznet_tick(void);

int wiznet_initialize(const uint32_t spiportnum);

int wiznet_set_hardware_address(const macaddress_t address);

int wiznet_get_hardware_address(macaddress_t address);

int wiznet_configure_network(const ipv4address_t address,
                            const ipv4address_t subnet,
                            const ipv4address_t gateway);

int wiznet_get_ipaddress(ipv4address_t address);

int wiznet_get_linkstate(int *linkstate);
