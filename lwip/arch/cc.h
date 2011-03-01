/* Toolchain definitions for ARM LWIP */

// $Id$

#ifndef __ARCH_CC_H__
#define __ARCH_CC_H__

#include <assert.h>
#include <stdio.h>

#define BYTE_ORDER LITTLE_ENDIAN

/* Define elemental data types */

typedef unsigned char	u8_t;
typedef unsigned short	u16_t;
typedef	unsigned int	u32_t;

typedef signed char	s8_t;
typedef signed short	s16_t;
typedef signed int	s32_t;

typedef u32_t mem_ptr_t;

/* Define (sn)printf formatters for these lwIP types */

#define U16_F		"hu"
#define S16_F		"hd"
#define X16_F		"hx"
#define U32_F		"u"
#define S32_F		"d"
#define X32_F		"x"

/* Compiler hints for packing structures */

#define PACK_STRUCT_FIELD(x)		x
#define PACK_STRUCT_STRUCT		__attribute__((packed))
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END

/* Define debug macros */

#define LWIP_PLATFORM_DIAG(...)		fprintf(stderr, __VA_ARGS__)
#define LWIP_PLATFORM_ASSERT(...)	{ fprintf(stderr, __VA_ARGS__); assert(0); }

#endif /* __ARCH_CC_H__ */
