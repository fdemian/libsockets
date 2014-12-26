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

#include "lib/sockets.h"
#include "lib/serializacion.c"
#include "lib/servidor.c"
#include "lib/comunes.c"

#define PUERTO 3490
#define MAX_CONEXIONES 10
#define LOCALHOST "127.0.0.1"

void actionServer(struct NIPCBin datos, int socket, int * matarServidor);
int manejarDesconexionServidor(int socketCliente);

int main(void)
{
  
  servidor(actionServer, PUERTO, MAX_CONEXIONES, manejarDesconexionServidor);
  
  return 0;
}

void actionServer(struct NIPCBin datos, int socket, int * matarServidor)
{
   char * mensajeRecibido = NULL;
   char * mensajeAEnviar = "Soy servidor."; 
   
   mensajeRecibido = (char *) datos.Payload; 
   
   printf("%d > %s\n", socket, mensajeRecibido);    
   mandarMensajeBinario(mensajeAEnviar, 1, strlen(mensajeAEnviar), socket);
}

int manejarDesconexionServidor(int socketCliente)
{
  printf("El cliente en el socket %d se desconecto.\n", socketCliente); 
  	
  return 0; 
}
