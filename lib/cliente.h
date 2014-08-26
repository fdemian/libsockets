#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFFSIZE 1024

#define SUCCESS 0  // A general variable representing sucess.

// Error codes. 
#define ERROR_CREATE  -1
#define ERROR_CONNECT -2
#define ERROR_RECEIVE_CLIEN -3
#define ERROR_SEND -4
#define ERROR_DESC -5
#define ERROR_RECV -6

int inicializar_cliente(char * ip, int puerto);
int mandarMensaje(char * mensaje, int tipoMensaje, int socket);
int esperarDatos(int socket, struct NIPC * datos);
void cerrar_cliente(int socket);

