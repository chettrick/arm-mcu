/* Utility program that waits for a TCP socket to be ready */

// $Id$

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tcp.h"

#define SERVERNAME	argv[1]
#define SERVERPORT	atoi(argv[2])
#define WAITTIME	atoi(argv[3])

static const char revision[] = "$Id$";

void main(int argc, char *argv[])
{
  uint32_t serveraddress;
  int timer = 0;
  int f;

  if (argc != 4)
  {
    fprintf(stderr, "Usage: %s <IP addr> <TCP port> <time>\n", argv[0]);
    exit(1);
  }

  serveraddress = resolve(SERVERNAME);
  if (serveraddress == 0L)
  {
    fprintf(stderr, "ERROR: Cannot resolve %s\n", SERVERNAME);
    exit(1);
  }

  for (timer = 0; timer < WAITTIME; timer++)
  {
    f = tcp_call(serveraddress, SERVERPORT);
    if (f > 0)
    {
      close(f);
      exit(0);
    }

    if (errno == ECONNREFUSED)
    {
      sleep(1);
      continue;
    }

    fprintf(stderr, "ERROR: tcp_call() failed, %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stderr, "ERROR: Timeout connecting to %s:%d\n", SERVERNAME, SERVERPORT);
  exit(1);
}
