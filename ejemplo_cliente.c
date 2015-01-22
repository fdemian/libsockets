#include "lib/NIPC.c"
#include "lib/cliente.c"
#include "lib/comunes.c"

#define PORT 3490

/*
 * This client serializes a message as a NIPC structure and sends it to the server. 
 * It then waits for a message from the server, prints it and terminates.
 */
int main(void)
{
  
  int socketDescriptor; 
  
  char * messageToSend = "You are a server.\0";
  char * answer = NULL; 
  struct package * dataRecieved = malloc(sizeof(struct package));  
  struct package packageToSend;
  
  struct NIPC unserializedDataRecieved;
  struct NIPC dataToSerialize;
  
  dataToSerialize.Type = 1;
  dataToSerialize.Length = strlen(messageToSend);
  dataToSerialize.Payload = (void *) messageToSend;
  packageToSend = NIPC_serialize(dataToSerialize);
  
  socketDescriptor = initializeClient(LOCALHOST, PORT);    
  sendMessage(packageToSend, socketDescriptor);  
  recieveData(socketDescriptor, dataRecieved);
  unserializedDataRecieved = NIPC_unserialize(dataRecieved->data);  
  
  answer = (char *) datosRecibidos.Payload;
   
  printf("%s\n", answer);
  
  // free memory.
  free(unserializedDataRecieved.Payload);
  free(packageToSend.data);
  free(dataRecieved->data);
  free(dataRecieved);
  
  closeClient(socketDescriptor); 
  
  return SUCCESS;
}
