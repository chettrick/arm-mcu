/* Internet Protocol services */

// $Id$

#include <sys/param.h>

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
#define htons(x)	__bswap_16(x)
#define ntohs(x)	__bswap_16(x)
#else
#error "Unsupported byte order!"
#endif

#define INET_ADDRSTRLEN		16
#define INET6_ADDRSTRLEN	46

char *inet_ntop(int af, const void *src, char *dst, int size);

int inet_pton(int af, const char *src, void *dst);
