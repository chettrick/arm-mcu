/* WizNet Driver Functions */

// $Id$

#include <errno.h>
#include <stdint.h>
#include <wiznet.h>

#define errno_r (*(__errno()))

int wiznet_bootp(ipv4address_t address,
                 ipv4address_t subnet,
                 ipv4address_t gateway,
                 ipv4address_t nameserver)
{
  int status = 0;

  return status;
}
