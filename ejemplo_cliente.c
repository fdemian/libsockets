#include "lib/NIPC.c"
#include "lib/cliente.c"
#include "lib/comunes.c"

#define PUERTO 3490
#define MAX_CONEXIONES 10

int main(void)
{
  
  int socketDescriptor; 
  
  char * mensaje = "Soy cliente.\0";
  char * respuesta = NULL; 
  struct package * dataRecieved = malloc(sizeof(struct package));  
  struct package packageToSend;
  
  struct NIPC datosRecibidos;
  struct NIPC dataToSerialize;
  
  dataToSerialize.Type = 1;
  dataToSerialize.Length = strlen(mensaje);
  dataToSerialize.Payload = (void *) mensaje;
  packageToSend = NIPC_serialize(dataToSerialize);
  
  socketDescriptor = initializeClient(LOCALHOST, PUERTO);    
  sendMessage(packageToSend, socketDescriptor);  
  recieveData(socketDescriptor, dataRecieved);
  datosRecibidos = NIPC_unserialize(dataRecieved->data);  
  
  respuesta = (char *) datosRecibidos.Payload;
   
  printf("%s\n", respuesta);
  
  // free memory.
  free(datosRecibidos.Payload);
  free(packageToSend.data);
  free(dataRecieved->data);
  free(dataRecieved);
  
  closeClient(socketDescriptor); 
  
  return SUCCESS;
}
