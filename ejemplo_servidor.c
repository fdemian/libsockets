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

void actionServer(struct NIPC datos, int socket);

int main(void)
{
  
  servidor(actionServer, PUERTO, MAX_CONEXIONES);
  
  return 0;
}

void actionServer(struct NIPC datos, int socket)
{
   printf("%d > %s\n", socket, datos.Payload);    
   mandarMensaje("Puto!", 40, socket);
}
