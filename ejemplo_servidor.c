#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h> 
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>


#include "lib/serializacion.c"
#include "lib/servidor.c"

#define PUERTO 3490
#define MAX_CONEXIONES 10
#define LOCALHOST "127.0.0.1"

void funcionLoca(struct NIPC datos, int socket);

int main(void)
{
  
  //int status = 0;  
  int * listener = malloc(sizeof(int));
  int * fdmax = malloc(sizeof(int));
  fd_set * master = malloc(sizeof(fd_set));
  fd_set * read_fds = malloc(sizeof(fd_set));
      
  inicializar_servidor(master, read_fds, listener, fdmax, MAX_CONEXIONES, PUERTO);
  servidor(funcionLoca, *fdmax, *listener, *master, *read_fds);
  
  return 0;
}

void funcionLoca(struct NIPC datos, int socket)
{
   printf("%d > %s\n", socket, datos.Payload);    
}