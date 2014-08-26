#include "servidor.h"

// Inicia el servidor con los parametros especificados.
int inicializar_servidor(fd_set * master, fd_set * read_fds, int * listener, int * fdmax,int max_conexiones, int puerto)
{

  struct sockaddr_in selfAddress;	
  int yes = 1;
			
  // Borra los conjuntos maestro y temporal						
  FD_ZERO(master); 
  FD_ZERO(read_fds); 
		
  // Obtener socket a la escucha
  if ((*listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    return ERROR_SOCKET;		
  }
	
  // Obviar el mensaje "address already in use" (la direccion ya se esta usando)
  if (setsockopt(*listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))== -1)
  {
    return ADDR_IN_USE;
  }

  // Enlazar
  selfAddress.sin_family = AF_INET;
  selfAddress.sin_addr.s_addr = INADDR_ANY;
  selfAddress.sin_port = htons(puerto);
  memset(&(selfAddress.sin_zero), '\0', 8);

  if (bind(*listener, (struct sockaddr *) &selfAddress, sizeof(selfAddress)) == -1) 
  {
    return ERROR_BIND;
  }

  // Escuchar	
  if (listen(*listener, max_conexiones) == -1) 
  {
    return ERROR_LISTEN;
  }
	
  // Agregar listener al conjunto maestro.
  FD_SET(*listener, master);

  // Seguir la pista del descriptor de fichero mayor
  *fdmax = *listener;
	
  return SUCCESS;
}

// Ejecuta la logica del servidor, iterando infinitamente.
void servidor(void (*manejadorDeDatos)(struct NIPC datos, int socket), int puerto, int maxConecciones)
{  
	
  struct sockaddr_in remoteaddr;	
  int connectionIndex = 0;
  int estadoDatosCliente;
  struct NIPC datosRecibidos;			  

  int * listener = malloc(sizeof(int));
  int * fdmax = malloc(sizeof(int));
  fd_set * master = malloc(sizeof(fd_set));
  fd_set * read_fds = malloc(sizeof(fd_set));

  datosRecibidos.Length = 0;
  datosRecibidos.Payload = NULL;
  datosRecibidos.Type = 0;
      
  inicializar_servidor(master, read_fds, listener, fdmax, maxConecciones, puerto);    

  for (;;) 
  {

    *read_fds = *master; // Copiar conjunto maestro.
    if (select(*fdmax + 1, read_fds, NULL, NULL, NULL ) == -1)
    {
      perror(" error en el select");
      break;
    }
    
    // explorar conexiones existentes en busca de datos que leer
    for (connectionIndex = 0; connectionIndex <= *fdmax; connectionIndex++)
    {
      if (FD_ISSET(connectionIndex, read_fds)) //tenemos datos!!
      {
        if (connectionIndex == *listener) 
        {
          // Handle new connections!
          handleConnection(&remoteaddr, *listener, fdmax, master);
        }
        else
        {					
          estadoDatosCliente = handleClientDataRecieved(connectionIndex, master,*fdmax, *listener, &datosRecibidos); 						
          if(estadoDatosCliente != ERROR_RECEIVE_SERV)
          {
            manejadorDeDatos(datosRecibidos, connectionIndex);
            free(datosRecibidos.Payload);
          }
        }
      }
    }
  }
    
  // Cerrar la conexion en el socket de escucha (del servidor) y borrar los conjuntos maestro y temporal.
  close(*listener); 
  FD_ZERO(master); 
  FD_ZERO(read_fds);

  // Liberar los datos allocados. 
  free(listener);
  free(fdmax);
  free(master);
  free(read_fds);

}

// Gestionar nuevas conexiones
void handleConnection(struct sockaddr_in * remoteaddr,int listener, int * fdmax, fd_set * master)
{   
 
  int addrlen = sizeof(*remoteaddr);
  int newfd; // descriptor de socket de nueva conexión aceptada
  
  if ((newfd = accept(listener,(struct sockaddr*) remoteaddr, (socklen_t *) &addrlen)) == -1) 
  {
	  perror("accept");
  }
  else 
  {
    FD_SET(newfd, master); // Agregar descriptor al conjunto maestro.
    if (newfd > *fdmax)
    {
      // Actualizar el maximo.
      *fdmax = newfd;
    }
  }  
}

// Gestionar datos de un cliente
int handleClientDataRecieved(int cliente, fd_set * master, int fdmax, int listener, struct NIPC * datos)
{

  int nbytes;  
  char buffer[BUFFSIZE]; // buffer para datos del cliente	        
  char * orden;
  struct Paquete paqueteRecibido;     
  
  if ((nbytes = recv(cliente, buffer, BUFFSIZE, 0)) <= 0) 
  {
    // Error o conexion cerrada por el cliente.
    close(cliente);
    FD_CLR(cliente, master); // Eliminar del conjunto maestro 
      
    return ERROR_RECEIVE_SERV;
  }
  else 
  { 
    // Tenemos datos del cliente.           
    orden = malloc(nbytes+1);
    memcpy(orden,buffer,nbytes);
    orden[nbytes] = '\0';    
    paqueteRecibido.Serializado = orden;
    paqueteRecibido.Length = nbytes;
    *datos = Deserializar(paqueteRecibido.Serializado); 
    free(orden);
  }
  
  return SUCCESS;  
}

/*
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
    return ERROR_SEND;
  }
 
  return SUCCESS;
}
*/
