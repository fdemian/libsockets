#include "cliente.h"

int initializeClient(char * ip, int port)
{  
  
  int targetSocket;
  struct sockaddr_in socketInfo;

  if ((targetSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    return ERROR_CREATE;
  }
  
  socketInfo.sin_family = AF_INET;
  socketInfo.sin_addr.s_addr = inet_addr(ip);
  socketInfo.sin_port = htons(port);
     
  if (connect(targetSocket, (struct sockaddr*) &socketInfo, sizeof(socketInfo))!= 0) 
  {
     return ERROR_CONNECT;
  }  
  
  return targetSocket;
}

int recieveData(int socket, struct package * dataRecieved)
{
  
  int bytesRecieved;
  int status;
  void * buffer = malloc(BUFFSIZE);
  
  bytesRecieved = recv(socket, buffer, BUFFSIZE, 0);
  
  if (bytesRecieved > 0)
  {
    
    dataRecieved->data = malloc(bytesRecieved);
    memcpy((dataRecieved->data), buffer, bytesRecieved);
    dataRecieved->length = bytesRecieved;    
    
    status = SUCCESS;
  }
  else
  {
    status = bytesRecieved == 0 ? ERROR_DESC : ERROR_RECV;
  }
  
  free(buffer);
    
  return status;
}

void closeClient(int socket)
{
  close(socket);
}
