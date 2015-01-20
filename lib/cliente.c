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


int recieveData(int socket, struct NIPC * data)
{
  
  int bytesRecieved;
  int status;
  void * buffer = malloc(BUFFSIZE);
  void * tempBuffer = NULL;
  struct package dataRecieved;

  bytesRecieved = recv(socket, buffer, BUFFSIZE, 0);

  if (bytesRecieved > 0)
  {

    tempBuffer = malloc(bytesRecieved);
    memcpy(tempBuffer, buffer, bytesRecieved);
    
    dataRecieved.data = tempBuffer;
    dataRecieved.length = bytesRecieved;

    *data = unserializePackage(dataRecieved.data);

    free(tempBuffer);    
    status = SUCCESS;
  }
  else
  {
    status = bytesRecieved == 0 ? ERROR_DESC : ERROR_RECV;
  }

  return status;
}

void closeClient(int socket)
{
  close(socket);  
}
