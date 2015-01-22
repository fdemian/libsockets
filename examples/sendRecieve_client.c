#include "../lib/client.c"
#include "../lib/commons.c"

#define PORT 3490

/*
 * This client serializes a message to the server. 
 * It then waits for a message from the server, prints it and terminates.
 */
int main(void)
{
  
  int socketDescriptor; 
  struct package packageToSend;
  struct package * dataRecieved = malloc(sizeof(struct package));
  char * messageToPrint = NULL; 
  
  packageToSend.data = "You are a server.\0"; 
  
  socketDescriptor = initializeClient(LOCALHOST, PORT);    
  sendMessage(packageToSend, socketDescriptor);  
  recieveData(socketDescriptor, dataRecieved);   
  
  messageToPrint = (char *) dataRecieved->data; 
  printf("%s\n", messageToPrint);
  
  //free(packageToSend.data);
  free(dataRecieved->data);
  free(dataRecieved);  
  closeClient(socketDescriptor); 
  
  return 0;
}
