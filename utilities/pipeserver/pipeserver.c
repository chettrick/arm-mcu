/* Bridge between a TCP server and a pair of FIFO's */

// $Id$

// Copyright (C)2013, Philip Munts, President, Munts AM Corp.
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


#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>

#define FIFONAME	argv[1]
#define PORTNUMBER	atoi(argv[2])

// Signal handler for SIGTERM

static bool exitflag = false;

static void exithandler(int sig)
{
  exitflag = true;
  signal(sig, exithandler);
}

static int tcp_answer_once(uint16_t myport)

{
  int s1, s2;
  struct sockaddr_in myaddr;

/* Attempt to create a socket */

  s1 = socket(AF_INET, SOCK_STREAM, 0);
  if (s1 < 0)
  {
    fprintf(stderr, "ERROR: socket() failed, errno=%d\n", errno);
    return -1;
  }

/* Attempt to bind socket */

  memset(&myaddr, 0, sizeof(myaddr));
  myaddr.sin_family = AF_INET;
  myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myaddr.sin_port = htons(myport);

  if (bind(s1, (struct sockaddr *)&myaddr, sizeof(myaddr)))
  {
    fprintf(stderr, "ERROR: bind() failed, errno=%d\n", errno);
    return -1;
  }

/* Establish incoming connection queue */

  if (listen(s1, 1))
  {
    fprintf(stderr, "ERROR: listen() failed, errno=%d\n", errno);
    return -1;
  }

/* Wait for incoming connection */

  s2 = accept(s1, NULL, NULL);
  if (s2 == -1)
  {
     fprintf(stderr, "ERROR: accept() failed, errno=%d\n", errno);
     return -1;
  }

  close(s1);
  return s2;
}

static void ShowUsage(void)
{
  puts("\nBridge between a pair of FIFO's and a TCP server\n");
  puts("Usage: pipeserver <filename> <port number>\n");
  exit(1);
}

int main(int argc, char *argv[])
{
  char fifoname_in[MAXPATHLEN];
  char fifoname_out[MAXPATHLEN];
  int fd_in;
  int fd_out;
  int s;
  fd_set readfds;
  struct timeval timeout;
  int status;
  int len;
  unsigned char buf[256];

// Validate command line arguments

  if (argc != 3)
    ShowUsage();

  if (PORTNUMBER == 0)
    ShowUsage();

// Install signal handlers

  if (signal(SIGINT, exithandler) == SIG_ERR)
  {
    fprintf(stderr, "ERROR: signal() for SIGINT failed, %s\n",
      strerror(errno));
    exit(1);
  }

  if (signal(SIGTERM, exithandler) == SIG_ERR)
  {
    fprintf(stderr, "ERROR: signal() for SIGTERM failed, %s\n",
      strerror(errno));
    exit(1);
  }

// Create and open fifo's

  memset(fifoname_in, 0, sizeof(fifoname_in));
  snprintf(fifoname_in, sizeof(fifoname_in), "%s.in", FIFONAME);

  if (mkfifo(fifoname_in, 0644))
  {
    fprintf(stderr, "ERROR: mkfifo() for %s failed, %s\n",
      fifoname_in, strerror(errno));
    exit(1);
  }

  fd_in = open(fifoname_in, O_RDONLY|O_NDELAY);
  if (fd_in < 0)
  {
    fprintf(stderr, "ERROR: open() for %s failed, %s\n",
      fifoname_in, strerror(errno));
    unlink(fifoname_in);
    exit(1);
  }

  memset(fifoname_out, 0, sizeof(fifoname_out));
  snprintf(fifoname_out, sizeof(fifoname_in), "%s.out", FIFONAME);

  if (mkfifo(fifoname_out, 0644))
  {
    fprintf(stderr, "ERROR: mkfifo() for %s failed, %s\n",
      fifoname_out, strerror(errno));
    close(fd_in);
    unlink(fifoname_in);
    exit(1);
  }

  fd_out = open(fifoname_out, O_RDWR|O_NDELAY);
  if (fd_out < 0)
  {
    fprintf(stderr, "ERROR: open() for %s failed, %s\n",
      fifoname_out, strerror(errno));
    close(fd_in);
    unlink(fifoname_in);
    unlink(fifoname_out);
    exit(1);
  }

// Switch to background process

  daemon(0, 0);

// Listen for incoming TCP connection

  s = tcp_answer_once(PORTNUMBER);
  if (s < 0)
  {
    close(fd_in);
    close(fd_out);
    unlink(fifoname_in);
    unlink(fifoname_out);
    exit(1);
  }

// Enter data transfer loop

  while (!exitflag)
  {
    FD_ZERO(&readfds);
    FD_SET(fd_in, &readfds);
    FD_SET(s, &readfds);

    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
    if (status == 0)
    {
      continue;
    }
    else if (status < 0)
    {
      break;
    }

    if (FD_ISSET(fd_in, &readfds))
    {
      len = read(fd_in, buf, sizeof(buf));
      if (len < 1) break;
      write(s, buf, len);
    }

    if (FD_ISSET(s, &readfds))
    {
      len = read(s, buf, sizeof(buf));
      if (len < 1) break;
      write(fd_out, buf, len);
    }
  }

// Do orderly shutdown

  close(fd_in);
  close(fd_out);
  close(s);

  unlink(fifoname_in);
  unlink(fifoname_out);

  exit(0);
}
