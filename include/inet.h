/* Internet Protocol services */

// $Id$

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
