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

// Map generic WizNet driver functions to W5100 driver functions

#if defined(WIZNET_W5100)
#include "W5100.h"

#define wiznet_initialize(x)			W5100_initialize(x)
#define wiznet_set_hardware_address(x)		W5100_set_hardware_address(x)
#define wiznet_get_hardware_address(x)		W5100_get_hardware_address(x)
#define wiznet_configure_network(x,y,z)		W5100_configure_network(x,y,z)
#define wiznet_get_ipaddress(x)			W5100_get_ipaddress(x)
#define wiznet_get_linkstate(x)			W5100_get_linkstate(x)
#define wiznet_tick()				W5100_tick()

// Map generic WizNet driver functions to W5200 driver functions

#elif defined(WIZNET_W5200)
#include "W5200.h"

#define wiznet_initialize(x)			W5200_initialize(x)
#define wiznet_set_hardware_address(x)		W5200_set_hardware_address(x)
#define wiznet_get_hardware_address(x)		W5200_get_hardware_address(x)
#define wiznet_configure_network(x,y,z)		W5200_configure_network(x,y,z)
#define wiznet_get_ipaddress(x)			W5200_get_ipaddress(x)
#define wiznet_get_linkstate(x)			W5200_get_linkstate(x)
#define wiznet_tick()				W5200_tick()

#else
#error WizNet device must be selected by defining WIZNET_W5100 or WIZNET_W5200
#endif
