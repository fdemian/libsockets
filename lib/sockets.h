#define BUFFSIZE 1024
#define MAX_CONNECTION_SERVER 3
#define SUCCESS 0 // Exito. 

// Codigos de error del servidor.

#define ERROR_SOCKET  -1
#define ADDR_IN_USE   -2   // Adress already in use (la direccion ya se esta usando)
#define ERROR_BIND    -3
#define ERROR_LISTEN  -4
#define ERROR_SEND    -5
#define ERROR_RECEIVE_SERV -6


// Codigos de error del cliente.

#define ERROR_CREATE  -1
#define ERROR_CONNECT -2
#define ERROR_RECEIVE_CLIEN -3
#define ERROR_DESC -5
#define ERROR_RECV -6

int mandarMensaje(char * mensaje, int tipoMensaje, int socket);