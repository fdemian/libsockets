#include <sys/select.h> 
#include "sockets.h"

/*
 * Starts a server in the specified port. 
 * 
 * dataHandler: a function that gets called whenever a socket sends data. 
 * port: the port used for listening to incoming connections. 
 * maxConnections: a hint indicating the maximum amount of connections. 
 * disconnectionHandler: a function that gets called whenever a socket is disconnected.  
 * 
 */
void startServer( void (*dataHandler)(struct package * datos, int socket, int * killServer), 
                  int port, int maxConnections, int (*disconnectionHandler)(int disconnectedSocket) );
