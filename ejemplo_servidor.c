#include "lib/sockets.h"
#include "lib/NIPC.c"
#include "lib/servidor.c"
#include "lib/comunes.c"

#define PUERTO 3490
#define MAX_CONEXIONES 10
#define LOCALHOST "127.0.0.1"

void actionServer(struct package * datosRecibidos, int socket, int * matarServidor);
int manejarDesconexionServidor(int socketCliente);

int main(void)
{
  
  startServer(actionServer, PUERTO, MAX_CONEXIONES, manejarDesconexionServidor);
  
  return 0;
}

void actionServer(struct package * datosRecibidos, int socket, int * matarServidor)
{
   char * mensajeRecibido = NULL;
   char * mensajeAEnviar = "Soy servidor.";    
   struct package packageToSend;
   struct NIPC dataToSerialize; 
   struct NIPC datosDesserializados; 
      
   datosDesserializados = NIPC_unserialize(datosRecibidos->data); 
   
   mensajeRecibido = (char *) datosDesserializados.Payload;    
   printf("%d > %s\n", socket, mensajeRecibido);  
   
   dataToSerialize.Type = 1;
   dataToSerialize.Length = strlen(mensajeAEnviar);
   dataToSerialize.Payload = (void *) mensajeAEnviar;
   
   packageToSend = NIPC_serialize(dataToSerialize);
       
   sendMessage(packageToSend, socket);
}

int manejarDesconexionServidor(int socketCliente)
{
  printf("El cliente en el socket %d se desconecto.\n", socketCliente); 
  	
  return 0; 
}
