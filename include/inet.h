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

#ifndef _INET_H
#define _INET_H

#include <sys/param.h>

_BEGIN_STD_C

// Network protocol macros

#define	AF_INET			2
#define AF_INET6		10

// Network byte order macros

#if BYTE_ORDER == BIG_ENDIAN
#define htonl(x)	(x)
#define ntohl(x)	(x)
#define htons(x)	(x)
#define ntohs(x)	(x)
#elif BYTE_ORDER == LITTLE_ENDIAN
#define htonl(x)	__bswap_32(x)
#define ntohl(x)	__bswap_32(x)
#define htons(x)	(((x << 8) & 0xff00) | ((x >> 8) & 0x00ff))
#define ntohs(x)	(((x << 8) & 0xff00) | ((x >> 8) & 0x00ff))
#else
#error "Unsupported byte order!"
#endif

#define INET_ADDRSTRLEN		16
#define INET6_ADDRSTRLEN	46

char *inet_ntop(int af, const void *src, char *dst, int size);

int inet_pton(int af, const char *src, void *dst);

_END_STD_C
#endif
