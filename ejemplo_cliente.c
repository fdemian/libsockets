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
#include "lib/cliente.c"
#include "lib/comunes.c"

#define PUERTO 3490
#define MAX_CONEXIONES 10
#define LOCALHOST "127.0.0.1"

int main(void)
{
  int socketDescriptor; 
  char * mensaje = "Soy cliente.";
  int tipoMensaje = 1;

  struct NIPCBin datos;
  char * respuesta = NULL; 
  
  socketDescriptor = inicializar_cliente(LOCALHOST, PUERTO);
  
  mandarMensajeBinario(mensaje, tipoMensaje, strlen(mensaje), socketDescriptor);
  
  esperarDatosBinario(socketDescriptor, &datos);

  respuesta = (char *) datos.Payload;

  printf("%s\n", respuesta);
  
  free(datos.Payload);
  
  return SUCCESS;
}
