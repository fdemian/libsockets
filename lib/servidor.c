#include "servidor.h"

// Inicia el servidor con los parametros especificados.
int inicializar_servidor(fd_set * master, fd_set * read_fds, int * listener, int * fdmax,int max_conexiones, int puerto)
{
	struct sockaddr_in selfAddress;
	
	int yes = 1; // para setsockopt() SO_REUSEADDR, mas abajo
			
        // borra los conjuntos maestro y temporal						
	FD_ZERO(master); 
	FD_ZERO(read_fds); 
		
	// obtener socket a la escucha
	if ((*listener = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		return ERROR_SOCKET;		
	}
	// obviar el mensaje "address already in use" (la direccion ya se esta usando)
	if (setsockopt(*listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))== -1)
	{
		return ADDR_IN_USE;
	}

	// enlazar
	selfAddress.sin_family = AF_INET;
	selfAddress.sin_addr.s_addr = INADDR_ANY;
	selfAddress.sin_port = htons(puerto);
	memset(&(selfAddress.sin_zero), '\0', 8);

	if (bind(*listener, (struct sockaddr *) &selfAddress, sizeof(selfAddress)) == -1) 
	{
		return ERROR_BIND;
	}

	// escuchar	
	if (listen(*listener, max_conexiones) == -1) {
		return ERROR_LISTEN;
	}
	
	// agregar listener al conjunto maestro	
	FD_SET(*listener, master);

	// Seguir la pista del descriptor de fichero mayor
	*fdmax = *listener;
	
	return SUCCESS;
}

void servidor(void (*manejadorDeDatos)(struct NIPC datos, int socket), int puerto, int maxConecciones)
{  	
  struct sockaddr_in remoteaddr;	
  int connectionIndex;
  int estadoDatosCliente;
  struct NIPC datosRecibidos;			  

    //int status = 0;  
  int * listener = malloc(sizeof(int));
  int * fdmax = malloc(sizeof(int));
  fd_set * master = malloc(sizeof(fd_set));
  fd_set * read_fds = malloc(sizeof(fd_set));
      
  inicializar_servidor(master, read_fds, listener, fdmax, maxConecciones, puerto);    


	for (;;) 
	{
		*read_fds = *master; // copiarlo
		if (select(*fdmax + 1, read_fds, NULL, NULL, NULL ) == -1) {
			perror(" error en el select");
			break;
		}

		// explorar conexiones existentes en busca de datos que leer
		for (connectionIndex = 0; connectionIndex <= *fdmax; connectionIndex++) {
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
					}
				}
			}
		}
	}    
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
	  FD_SET(newfd, master); // agregar al conjunto maestro
	  if (newfd > *fdmax)
	  {
		  // actualizar el maximo
		  *fdmax = newfd;
	  }
  }  
}

// Gestionar datos de un cliente
int handleClientDataRecieved(int cliente,fd_set * master, int fdmax, int listener, struct NIPC * datos)
{
  int nbytes;  
  char buffer[BUFFSIZE]; // buffer para datos del cliente	        
  char * orden;
  struct Paquete paqueteRecibido;     
  
  if ((nbytes = recv(cliente, buffer, BUFFSIZE, 0)) <= 0) 
  {
    // error o conexion cerrada por el cliente
    close(cliente); // hasta luego!
    FD_CLR(cliente, master); // eliminar del conjunto maestro       
    return ERROR_RECEIVE_SERV;
  }
  else 
  { 
    // tenemos datos del cliente           
    orden = malloc(nbytes+1);
    memcpy(orden,buffer,nbytes);
    orden[nbytes] = '\0';    
    paqueteRecibido.Serializado = orden;
    paqueteRecibido.Length = nbytes;
    *datos = Deserializar(paqueteRecibido.Serializado);        
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
// cierra la conexion y borra los conjuntos maestro y temporal
void cerrar_servidor(int socket, fd_set * master, fd_set * read_fds)
{
  close(socket); 
  FD_ZERO(master); 
  FD_ZERO(read_fds);
}
