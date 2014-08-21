#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define BUFF_SIZE 1024



#define SUCCESS 0  // A general variable representing sucess.

// Define error codes.
#define ERROR_CREATE  -1
#define ERROR_CONNECT -2
#define ERROR_RECEIVE_CLIEN -3

int inicializar_cliente( struct sockaddr_in * socketInfo, int * socketDestino,char * ip, int puerto);
void cerrar_cliente(int socket);
//void mandarMensaje(char * mensaje,int tipoMensaje,int destinatario);
//struct NIPC esperarDatos(int);
