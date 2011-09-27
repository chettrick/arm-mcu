/* WizNet Driver Function Prototypes */

// $Id$

#if defined(WIZNET_W5200)
#include "W5200.h"

#define wiznet_initialize(x)			W5200_initialize(x)
#define wiznet_set_hardware_address(x)		W5200_set_hardware_address(x)
#define wiznet_get_hardware_address(x)		W5200_get_hardware_address(x)
#define wiznet_configure_network(x,y,z)		W5200_configure_network(x,y,z)
#define wiznet_get_ipaddress(x)			W5200_get_ipaddress(x)
#define wiznet_get_linkstate(x)			W5200_get_linkstate(x)
#define wiznet_tick()				W5200_tick()
#else
#error WizNet device must be selected by defining WIZNET_DEVICE
#endif
