#include "lib/sockets.h"
#include "lib/serializacion.c"
#include "lib/servidor.c"
#include "lib/comunes.c"

#define PUERTO 3490
#define MAX_CONEXIONES 10
#define LOCALHOST "127.0.0.1"

void actionServer(struct NIPC datos, int socket, int * matarServidor);
int manejarDesconexionServidor(int socketCliente);

int main(void)
{
  
  startServer(actionServer, PUERTO, MAX_CONEXIONES, manejarDesconexionServidor);
    
  return 0;
}

void actionServer(struct NIPC datos, int socket, int * matarServidor)
{
   char * mensajeRecibido = NULL;
   char * mensajeAEnviar = "Soy servidor."; 
   
   mensajeRecibido = (char *) datos.Payload; 
   
   printf("%d > %s\n", socket, mensajeRecibido);    
   sendMessage(mensajeAEnviar, 1, strlen(mensajeAEnviar), socket);
}

int manejarDesconexionServidor(int socketCliente)
{
  printf("El cliente en el socket %d se desconecto.\n", socketCliente); 
  	
  return 0; 
}
