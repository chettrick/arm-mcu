/* TCP/IP socket API (Application Programming Interface.  These functions are */
/* implemented in the various network device drivers and server to bind those */
/* drivers to the ARM device infrastructure.  When the following functions    */
/* are implemented and registered to a file discriptor using the              */
/* device_register_char() function, the TCP/IP socket can then be completely  */
/* manipulated via the formal file I/O functions such as open(), read() and   */
/* like.                                                                      */

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

#ifndef _SOCKET_H
#define _SOCKET_H

_BEGIN_STD_C

extern int socket_open(char *name, unsigned int *subdevice);

extern int socket_close(unsigned int subdevice);

extern int socket_write(unsigned int subdevice, char *buf, unsigned int count);

extern int socket_read(unsigned int subdevice, char *buf, unsigned int count);

extern int socket_write_ready(unsigned int subdevice);

extern int socket_read_ready(unsigned int subdevice);

_END_STD_C
#endif
