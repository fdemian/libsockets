#include <sys/select.h> 
#include "server.h"

/*
 * Static functions / Private API. 
 */ 
static int initializeServer(fd_set * master, fd_set * read_fds, int * listener, int * fdmax, int maxConnections, int port);
static int handleConnection(struct sockaddr_in * remoteaddr,int listener, int * fdmax, fd_set * master);
static int handleClientDataRecieved(int client, fd_set * master, int fdmax, int listener, struct package * dataRecieved, int (*disconnectionHandler)(int cliente), int * killServer);

void 
startServer(void (*dataHandler)(struct package * data, int socket, int * killServer), int port, int maxConnections,int (*disconnectionHandler)(int disconnectedSocket))
{  
	
  struct sockaddr_in remoteaddr;	
  int connectionIndex = 0;
  int recieveStatus = 0;
  
  int killServer = 0;
  int * listener = malloc(sizeof(int));
  int * fdmax = malloc(sizeof(int));
  fd_set * master = malloc(sizeof(fd_set));
  fd_set * read_fds = malloc(sizeof(fd_set));  
  
  struct package * recievedData = malloc(sizeof(struct package)); 
  
  initializeServer(master, read_fds, listener, fdmax, maxConnections, port);    
 
  while(!killServer)
  {	  
    *read_fds = *master;
    
    if(select(*fdmax + 1, read_fds, NULL, NULL, NULL) != -1)
    {
      for (connectionIndex = 0; connectionIndex <= *fdmax; connectionIndex++)
      {
      
        if (FD_ISSET(connectionIndex, read_fds))
        {
          if (connectionIndex == *listener) 
          {
            handleConnection(&remoteaddr, *listener, fdmax, master);
          }
          else
          {					
            recieveStatus = handleClientDataRecieved(connectionIndex, master,*fdmax, *listener, recievedData, disconnectionHandler, &killServer);
          
            if(recieveStatus != ERROR_RECEIVE_SERV)
            {
              dataHandler(recievedData, connectionIndex, &killServer);
            }
          }
        }
      }
    }
    else
    {
	   killServer = 1; 	
    }
    
  }
    
  // Close the listening socket's connection and clear master and temporary sets. 
  close(*listener); 
  FD_ZERO(master); 
  FD_ZERO(read_fds);

  // Deallocate memmory. 
  free(listener);
  free(fdmax);
  free(master);
  free(read_fds);

}


/* ------------------------- Private functions ------------------------- */

static int 
handleConnection(struct sockaddr_in * remoteaddr, int listener, int * fdmax, fd_set * master)
{   
  int addrlen = sizeof(*remoteaddr);
  int newfd;
  
  newfd = accept(listener,(struct sockaddr*) remoteaddr, (socklen_t *) &addrlen);
  
  if(newfd == -1) 
  {
    return ERROR_ACCEPT;  
  }
  else 
  {
    FD_SET(newfd, master);
    
    if (newfd > *fdmax)
    {
      *fdmax = newfd;      
    }
    
    return SUCCESS; 
  }
}


static int 
handleClientDataRecieved(int clientSocket, fd_set * master, int fdmax, int listener, struct package * dataRecieved, int (*disconnectionHandler)(int cliente), int * killServer)
{
  
  int bytesRecieved;  
  void * buffer = malloc(BUFFSIZE);
  
  bytesRecieved = recv(clientSocket, buffer, BUFFSIZE, 0);    
      
  if(bytesRecieved > 0) 
  {
    
    dataRecieved->data = malloc(bytesRecieved);   
    memcpy(dataRecieved->data, buffer, bytesRecieved);
    dataRecieved->length = bytesRecieved;  
                          
  }
  else 
  { 
    if(disconnectionHandler(clientSocket) == -1)
    {
      *killServer = 1;  	
    }
    
    close(clientSocket);
    FD_CLR(clientSocket, master);
    
    return ERROR_RECEIVE_SERV;
  }
  
  return SUCCESS;  
}


static int 
initializeServer(fd_set * master, fd_set * read_fds, int * listener, int * fdmax, int maxConnections, int port)
{
  
  struct sockaddr_in selfAddress;	
  int yes = 1;
  
  // Clear master and temporary sets. 
  FD_ZERO(master); 
  FD_ZERO(read_fds); 
  	
  if ((*listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    return ERROR_SOCKET;		
  }
  
  if (setsockopt(*listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))== -1)
  {
    return ADDR_IN_USE;
  }
  
  selfAddress.sin_family = AF_INET;
  selfAddress.sin_addr.s_addr = INADDR_ANY;
  selfAddress.sin_port = htons(port);
  memset(&(selfAddress.sin_zero), '\0', 8);

  if (bind(*listener, (struct sockaddr *) &selfAddress, sizeof(selfAddress)) == -1) 
  {
    return ERROR_BIND;
  }

  if (listen(*listener, maxConnections) == -1) 
  {
    return ERROR_LISTEN;
  }
	
  // Add listener to master set. 
  FD_SET(*listener, master);

  // Keep track of the greatest file descriptor. 
  *fdmax = *listener;
  
  return SUCCESS;
}
