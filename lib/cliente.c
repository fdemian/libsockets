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

int mandarMensaje(char * mensaje, int tipoMensaje, int socket)
{

  struct Paquete recibido;
  struct NIPC paqueteAMandar;

  paqueteAMandar.Type = tipoMensaje;
  paqueteAMandar.Length = strlen(mensaje);
  paqueteAMandar.Payload = mensaje;

  recibido = Serializar(paqueteAMandar);

  if(send(socket, recibido.Serializado, recibido.Length, 0)== -1)
  {
    return ERROR_SEND;
  }

  free(recibido.Serializado);

  return SUCCESS;
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

void cerrar_cliente(int socket)
{
  close(socket);  
}
