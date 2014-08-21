#include "comunes.h"

int mandarMensaje(char * mensaje,int tipoMensaje,int socket)
{
	struct Paquete recibido;
	struct NIPC paqueteAMandar;

	paqueteAMandar.Type = tipoMensaje;
	paqueteAMandar.Length = strlen(mensaje);
	paqueteAMandar.Payload = mensaje;
	recibido = Serializar(paqueteAMandar);
	if(send(socket,recibido.Serializado , recibido.Length , 0)== -1)
	{
	  //return ERROR_SEND;
		printf("Error al mandar mensaje tipo %i del socket %i con payload: %s",paqueteAMandar.Type,socket,mensaje);
		return ERROR_SEND;
	}

	return SUCCESS;
}

struct NIPC esperarDatos(int socket)
{
   int nbytesRecibidos;
   char buffer[BUFFSIZE];
   char * orden;
   struct Paquete recibido;
   struct NIPC mensaje;

   nbytesRecibidos = recv(socket, buffer, BUFFSIZE, 0);
   
   if (nbytesRecibidos > 0)
    {
      orden = malloc(nbytesRecibidos+1);
      memcpy (orden,buffer,nbytesRecibidos);
      orden[nbytesRecibidos] = '\0';
      recibido.Serializado = orden;
      recibido.Length = nbytesRecibidos;
      mensaje = Deserializar(recibido.Serializado);
      free(orden);
    } 
    else if (nbytesRecibidos == 0)
    {
        // Bytes recibidos = 0  -> se desconecto el socket
    	orden = malloc(1);
    	orden = strdup("");
    	orden[nbytesRecibidos] = '\0';
    	recibido.Serializado = orden;
    	recibido.Length = nbytesRecibidos;
    	mensaje.Type = ERROR_DESC;
    	free(orden);
    } else {
    	// Bytes recibidos < 0  -> hubo un error.
    	orden = malloc(1);
    	orden = strdup("");
    	orden[nbytesRecibidos] = '\0';
    	recibido.Serializado = orden;
    	recibido.Length = nbytesRecibidos;
    	mensaje.Type = ERROR_RECV;
    	free(orden);
    }

    return mensaje;
}


/*
int mandarMensajeConLog(char * mensaje,int tipoMensaje,int socket,t_log* log){

	struct Paquete recibido;
	struct NIPC paqueteAMandar;

	paqueteAMandar.Type = tipoMensaje;
	paqueteAMandar.Length = strlen(mensaje);
	paqueteAMandar.Payload = mensaje;
	recibido = Serializar(paqueteAMandar);
	if(send(socket,recibido.Serializado , recibido.Length , 0)== -1)
	{
	  return ERROR_SEND;
	}

	log_debug(log,"Se envia mensaje de tipo %i, con Payload: %s, y Longitud: %i",paqueteAMandar.Type,paqueteAMandar.Payload,paqueteAMandar.Length);
	return SUCCESS;
}



struct NIPC esperarDatosConLog(int socket, t_log* log){
	 int nbytesRecibidos;
	   char buffer[BUFFSIZE];
	   char * orden;
	   struct Paquete recibido;
	   struct NIPC mensaje;

	   if ((nbytesRecibidos = recv(socket, buffer, BUFFSIZE, 0))> 0)
	    {
	      orden = malloc(nbytesRecibidos+1);
	      memcpy (orden,buffer,nbytesRecibidos);
	      orden[nbytesRecibidos] = '\0';
	      recibido.Serializado = orden;
	      recibido.Length = nbytesRecibidos;
	      mensaje = Deserializar(recibido.Serializado);
	    }
	    else if ((nbytesRecibidos = recv(socket, buffer, BUFFSIZE, 0)) == 0)
	    {
	      //TODO retornar ERROR_RECIEVE manejar el mensaje de manera distinta.
	      //perror("Error al recibir datos");
	      orden = malloc(1);
	      orden = strdup("");
	      orden[nbytesRecibidos] = '\0';
	      recibido.Serializado = orden;
	      recibido.Length = nbytesRecibidos;
	      mensaje.Type = ERROR_RECV;
	    } else {
	    	//TODO retornar ERROR_RECIEVE manejar el mensaje de manera distinta.
	    	//perror("Error al recibir datos");
	    	orden = malloc(1);
	    	orden = strdup("");
	    	orden[nbytesRecibidos] = '\0';
	    	recibido.Serializado = orden;
	    	recibido.Length = nbytesRecibidos;
	    	mensaje.Type = ERROR_RECV;
	    }

		log_debug(log,"Se recibe un mensaje de tipo %i, con Payload: %s, y Longitud: %i",mensaje.Type,mensaje.Payload,mensaje.Length);
	    return mensaje;
}
*/
