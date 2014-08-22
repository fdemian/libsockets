#define BUFFSIZE 1024

#define MAX_CONNECTION_SERVER 3
#define SUCCESS 0 // A constant to indicate general sucess.

// Define error types.

#define ERROR_SOCKET  -1
#define ADDR_IN_USE   -2  //Adress already in use (la direccion ya se esta usando)
#define ERROR_BIND    -3
#define ERROR_LISTEN  -4
#define ERROR_SEND    -5
#define ERROR_RECEIVE_SERV -6


int inicializar_servidor(fd_set * master, fd_set * read_fds, int * listener, int * fdmax, int max_conexiones, int puerto);
void servidor(void (*manejadorDeDatos)(struct NIPC datos, int socket), int puerto, int maxConecciones);
void cerrar_servidor(int socket, fd_set * master, fd_set * read_fds);
void handleConnection(struct sockaddr_in * remoteaddr,int listener, int * fdmax, fd_set * master);
int handleClientDataRecieved(int cliente,fd_set * master, int fdmax, int listener, struct NIPC * datos);
//int mandarMensaje(char * mensaje,int tipoMensaje,int socket);
