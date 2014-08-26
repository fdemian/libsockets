#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h> 
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>


#include "lib/serializacion.c"
#include "lib/cliente.c"

#define PUERTO 3490
#define MAX_CONEXIONES 10
#define LOCALHOST "127.0.0.1"

int main(void)
{
  int socketDescriptor; 
  char * mensaje = "Hola!";
  int tipoMensaje = 1;
  
  socketDescriptor = inicializar_cliente(LOCALHOST, PUERTO);
  mandarMensaje(mensaje, tipoMensaje, socketDescriptor);
   
  return SUCCESS;
}
