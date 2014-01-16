/* Internet Protocol services */

// $Id$

// Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

static const char revision[] = "$Id$";

#include <stdio.h>
#include <string.h>

#include <cpu.h>
#include <inet.h>

char *inet_ntop(int af, const void *src, char *dst, int size)
{
  const uint8_t *bytes = (uint8_t *) src;

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
      snprintf(dst, size, "%d.%d.%d.%d",
               bytes[0], bytes[1], bytes[2], bytes[3]);
      return dst;
      break;

    default :
      errno_r = EAFNOSUPPORT;
      return NULL;
  }
}

int inet_pton(int af, const char *src, void *dst)
{
  uint8_t *bytes = (uint8_t *) dst;
  unsigned int a, b, c, d;

  switch (af)
  {
    case AF_INET :
      // NOTE: sscanf() with %hhu corrupts the byte following the last argument
      // so we convert to unsigned integer first and then copy to the bytes.
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
