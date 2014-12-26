int inicializar_servidor(fd_set * master, fd_set * read_fds, int * listener, int * fdmax, int max_conexiones, int puerto);
void servidor(void (*manejadorDeDatos)(struct NIPCBin datos, int socket, int * cerrarServidor), int puerto, int maxConecciones,int (*manejadorDeDesconexion)(int cliente));
void cerrar_servidor(int socket, fd_set * master, fd_set * read_fds);
void handleConnection(struct sockaddr_in * remoteaddr,int listener, int * fdmax, fd_set * master);
int handleClientDataRecieved(int cliente, fd_set * master, int fdmax, int listener, struct NIPCBin * datos, int (*manejadorDeDesconexion)(int cliente), int * killServer);
