#include "../lib/NIPC.c"
#include "../lib/server.c"
#include "../lib/commons.c"

#define PORT 3490
#define MAX_CONNECTIONS 10

void actionServer(struct package * datosRecibidos, int socket, int * matarServidor);
int handleDisconnection(int clientSocket);

int main(void)
{
  startServer(actionServer, PORT, MAX_CONNECTIONS, handleDisconnection);
  
  return 0;
}

/*  
 *  In this example we wait for a socket to send us data.
 *  Once it does the body of actionServer is executed, unserializing the data that was sent and printing it. 
 *  It then sends a NIPC-serialized message to the socket in question.  
 */
void actionServer(struct package * dataRecieved, int socket, int * killServer)
{
   char * messageRecieved = NULL;
   char * messageToSend = "You are the client.";    
   struct package packageToSend;
   struct NIPC dataToSerialize; 
   struct NIPC unserializedData; 
      
   unserializedData = NIPC_unserialize(dataRecieved->data); 
   
   messageRecieved = (char *) unserializedData.Payload;    
   printf("%d > %s\n", socket, messageRecieved);  
   
   dataToSerialize.Type = 1;
   dataToSerialize.Length = strlen(messageToSend);
   dataToSerialize.Payload = (void *) messageToSend;
   
   packageToSend = NIPC_serialize(dataToSerialize);
       
   sendMessage(packageToSend, socket);
}

int handleDisconnection(int clientSocket)
{
  printf("Socket %d disconnected.\n", clientSocket); 
  
  return 0; 
}
