
# Flags de compilacion.
# Convierte todos los warnings en errores.
FLAGS = -Werror -Wall -g -ggdb

# Programas a compilar.
SEVER_SOURCE = example1_server.c 
SEVER_NAME = serv1

CLIENT_SOURCE = example1_client.c 
CLIENT_NAME = cli1

SENDREC_SERVER_SOURCE = sendrec_server.c
SENDREC_SERVER_NAME = serv2

SENDREC_CLIENT_SOURCE = sendrec_client.c
SENDREC_CLIENT_NAME = cli2


# Agregar las dependencias de compilacion aca.
#DEPENDS = 

all:	example_client example_server sendrec_client sendrec_server

example_client:
	$(CC) $(FLAGS) $(CLIENT_SOURCE) -o $(CLIENT_NAME)

example_server: 
	$(CC) $(FLAGS) $(SEVER_SOURCE) -o $(SEVER_NAME)

sendrec_client: 
	$(CC) $(FLAGS) $(SENDREC_CLIENT_SOURCE) -o $(SENDREC_CLIENT_NAME)

sendrec_server:
	$(CC) $(FLAGS) $(SENDREC_SERVER_SOURCE) -o $(SENDREC_SERVER_NAME)

clean:
	rm $(SEVER_NAME)
	rm $(CLIENT_NAME)
	rm $(SENDREC_SERVER_NAME)
	rm $(SENDREC_CLIENT_NAME)
