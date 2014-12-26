#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int inicializar_cliente(char * ip, int puerto);
int esperar_datos(int socket, struct NIPCBin * datos);
void cerrar_cliente(int socket);
