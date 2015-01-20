#define BUFFSIZE 1024
#define LOCALHOST "127.0.0.1"

// Error codes. 

// Server
#define ERROR_SOCKET  -1
#define ADDR_IN_USE   -2
#define ERROR_BIND    -3   
#define ERROR_LISTEN  -4
#define ERROR_SEND    -5
#define ERROR_RECEIVE_SERV -6
#define ERROR_ACCEPT -7

// Client
#define ERROR_CREATE  -1
#define ERROR_CONNECT -2
#define ERROR_RECEIVE_CLIEN -3
#define ERROR_DESC -5
#define ERROR_RECV -6

#define SUCCESS 0

/*
 * Sends a message to a given socket. 
 */
int sendMessage(void * mensaje, int tipoMensaje, int largo, int socket);
