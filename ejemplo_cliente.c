#include "lib/sockets.h"
#include "lib/serializacion.c"
#include "lib/cliente.c"
#include "lib/comunes.c"

#define PUERTO 3490
#define MAX_CONEXIONES 10

int main(void)
{
  int socketDescriptor; 
  char * mensaje = "Soy cliente.";
  int tipoMensaje = 1;

  struct NIPC datos;
  char * respuesta = NULL; 
  
  socketDescriptor = initializeClient(LOCALHOST, PUERTO);  
  sendMessage(mensaje, tipoMensaje, strlen(mensaje), socketDescriptor);  
  recieveData(socketDescriptor, &datos);

  respuesta = (char *) datos.Payload;

  printf("%s\n", respuesta);
  
  free(datos.Payload);
  closeClient(socketDescriptor); 
  
  return SUCCESS;
}
