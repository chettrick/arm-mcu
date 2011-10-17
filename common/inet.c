/* Internet Protocol services */

// $Id$

#include <cpu.h>
#include <errno.h>
#include <inet.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

char *inet_ntop(int af, const void *src, char *dst, int size)
{
  const uint8_t *bytes = src;

  if ((src == NULL) || (dst == NULL))
  {
    errno_r = EINVAL;
    return NULL;
  }

  switch (af)
  {
    case AF_INET :
      if (size < INET_ADDRSTRLEN)
      {
        errno_r = EINVAL;
        return NULL;
      }

      memset(dst, 0, size);
      snprintf(dst, size, "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);
      return dst;
      break;

    default :
      errno_r = EAFNOSUPPORT;
      return NULL;      
  }
}

int inet_pton(int af, const char *src, void *dst)
{
  uint8_t *bytes = dst;
  unsigned int a, b, c, d;

  switch (af)
  {
    case AF_INET :
      // NOTE: sscanf() with %hhu corrupts the byte following the last argument
      // so we convert to unsigned integers first and then copy them to the bytes.
      if (sscanf(src, "%u.%u.%u.%u", &a, &b, &c, &d) == 4)
      {
        bytes[0] = a;
        bytes[1] = b;
        bytes[2] = c;
        bytes[3] = d;
        return 1;
      }

      errno_r = EINVAL;
      return 0;
      break;

    default :
      errno_r = EAFNOSUPPORT;
      return -1;      
  }
}
