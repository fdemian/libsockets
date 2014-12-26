#include "cliente.h"

int inicializar_cliente(char * ip, int puerto)
{  
  
  int socketDestino;
  struct sockaddr_in socketInfo;

  if ((socketDestino = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    return ERROR_CREATE;
  }

  socketInfo.sin_family = AF_INET;
  socketInfo.sin_addr.s_addr = inet_addr(ip);
  socketInfo.sin_port = htons(puerto);
    
  if (connect(socketDestino, (struct sockaddr*) &socketInfo, sizeof(socketInfo))!= 0) 
  {
     return ERROR_CONNECT;
  }  
  
   return socketDestino;
}

int esperarDatos(int socket, struct NIPC * datos)
{

  int nbytesRecibidos;
  int status; 
  char buffer[BUFFSIZE];
  char * orden;
  struct Paquete recibido;

  nbytesRecibidos = recv(socket, buffer, BUFFSIZE, 0);
   
  if (nbytesRecibidos > 0)
  {

    orden = malloc(nbytesRecibidos+1);
    memcpy (orden,buffer,nbytesRecibidos);
    orden[nbytesRecibidos] = '\0';
    recibido.Serializado = orden;
    recibido.Length = nbytesRecibidos;

    *datos = Deserializar(recibido.Serializado);

    free(orden);       

    status = SUCCESS;    

  } 
  else
  {
    // Error.
    status = nbytesRecibidos == 0 ? ERROR_DESC : ERROR_RECV;
  }

  return status;
}

int esperarDatosBinario(int socket, struct NIPCBin * datos)
{

  int nbytesRecibidos;
  int status;
  void * buffer = malloc(BUFFSIZE);
  void * orden;
  struct Paquete recibido;

  nbytesRecibidos = recv(socket, buffer, BUFFSIZE, 0);

  if (nbytesRecibidos > 0)
  {

    orden = malloc(nbytesRecibidos);
    memcpy (orden,buffer,nbytesRecibidos);
    recibido.Serializado = orden;
    recibido.Length = nbytesRecibidos;

    *datos = DeserializarBinario(recibido.Serializado);

    free(orden);

    status = SUCCESS;

  }
  else
  {
    // Error.
    status = nbytesRecibidos == 0 ? ERROR_DESC : ERROR_RECV;
  }

  return status;
}

void cerrar_cliente(int socket)
{
  close(socket);  
}
