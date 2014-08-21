#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define ERROR_SEND  -5
#define ERROR_RECV  250
#define ERROR_DESC  251
#define ERROR_RECEPCION -8
#define BUFFSIZE 1024

int mandarMensaje(char * mensaje,int tipoMensaje,int socket);
struct NIPC esperarDatos(int);
//int mandarMensajeConLog(char * mensaje,int tipoMensaje,int socket,t_log* log);
//struct NIPC esperarDatosConLog(int socket, t_log* log);
