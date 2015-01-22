#include <sys/select.h> 

/*
 * Starts a server in the specified port. 
 * 
 * manejadorDeDatos: a function that gets called whenever a socket sends data. 
 * puerto: the port used for listening to incoming connections. 
 * maxConecciones: a hint indicating the maximum amount of connections. 
 * manejadorDeDesconexion: a function that gets called whenever a socket is disconnected.  
 * 
 */
void startServer(void (*dataHandler)(struct package * datos, 
              int socket, int * killServer), int puerto, int maxConnections,
              int (*disconnectionHandler)(int disconnectedSocket));
