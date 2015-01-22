#include "lib/server.c"
#include "lib/commons.c"

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
 *  Once it does the body of actionServer is executed, printing it. 
 *  It then sends a message to the socket in question.
 */
void actionServer(struct package * dataRecieved, int socket, int * killServer)
{   
   struct package packageToSend; 
        
   printf("%d > %s\n", socket, (char *) dataRecieved->data);  
      
   packageToSend.data = "You are the client.\0";
   packageToSend.length = strlen("You are the client.\0");
   
   sendMessage(packageToSend, socket);
}

int handleDisconnection(int clientSocket)
{
  printf("Socket %d disconnected.\n", clientSocket); 
  
  return 0; 
}
