# Makefile for tcpwait utility

# $Id$

CFLAGS		= -Wall

default: tcpwait

tcpwait: tcpwait.c tcp.h
	$(CC) $(CFLAGS) -o tcpwait tcpwait.c

install: tcpwait
	install -csm 0555 tcpwait	/usr/local/bin

clean:
	-rm tcpwait
