#ifndef _LSOCKETS_H_

#define _LSOCKETS_H_

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFSIZE 1024
#define LOCALHOST "127.0.0.1"

// Error codes. 

// Server
#define ERROR_SOCKET  -1
#define ADDR_IN_USE   -2
#define ERROR_BIND    -3   
#define ERROR_LISTEN  -4
#define ERROR_SEND    -5
#define ERROR_RECEIVE_SERV -6
#define ERROR_ACCEPT -7

// Client
#define ERROR_CREATE  -1
#define ERROR_CONNECT -2
#define ERROR_RECEIVE_CLIEN -3
#define ERROR_DESC -5
#define ERROR_RECV -6

#define SUCCESS 0

struct package
{
  void * data;
  int length;
};

/*
 * Sends a message to a given socket. 
 */
int sendMessage(struct package dataToSend, int socket);

#endif
