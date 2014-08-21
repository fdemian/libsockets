#include "cliente.h"
#include "serializacion.c"

int inicializar_cliente( struct sockaddr_in * socketInfo, int * socketDestino,char * ip, int puerto)
{  
  
  if (((*socketDestino) = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    return ERROR_CREATE;
  }

  (*socketInfo).sin_family = AF_INET;
  (*socketInfo).sin_addr.s_addr = inet_addr(ip);
  (*socketInfo).sin_port = htons(puerto);
    
  if (connect((*socketDestino), (struct sockaddr*) socketInfo, sizeof(*socketInfo))!= 0) 
  {
    return ERROR_CONNECT;
  }  
  
   return SUCCESS;
}

/*
void mandarMensaje(char * mensaje,int tipoMensaje,int destinatario)
{
	struct Paquete recibido;
	struct NIPC paqueteAMandar; 		
	
	paqueteAMandar.Type = tipoMensaje;
	paqueteAMandar.Length = strlen(mensaje);
	paqueteAMandar.Payload = mensaje;
	recibido = Serializar(paqueteAMandar);
	send(destinatario,recibido.Serializado , recibido.Length , 0); 		
}
*/

void cerrar_cliente(int socket)
{
  close(socket);  
}
