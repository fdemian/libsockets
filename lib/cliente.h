#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/* 
 * Crea un socket cliente en la maquina actual 
 * y se conecta a otro socket en la IP y Puerto especificados.
 */
int initializeClient(char * ip, int port);

/*
 * Se bloquea esperando datos del socket al cual esta conectado. 
 */
int recieveData(int socket, struct NIPC * datos);

/*
 * Cierra la conexion. 
 */
void closeClient(int socket);
