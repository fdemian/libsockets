
# Flags de compilacion.
# Convierte todos los warnings en errores.
FLAGS = -Werror -Wall -g -ggdb

# Programas a compilar.
SEVER_SOURCE = ejemplo_servidor.c 
SEVER_NAME = serv

CLIENT_SOURCE = ejemplo_cliente.c 
CLIENT_NAME = cli

# Agregar las dependencias de compilacion aca.
#DEPENDS = 

main:
	$(CC) $(FLAGS) $(SEVER_SOURCE) -o $(SEVER_NAME)
	$(CC) $(FLAGS) $(CLIENT_SOURCE) -o $(CLIENT_NAME)

client:
	$(CC) $(FLAGS) $(CLIENT_SOURCE) -o $(CLIENT_NAME)

server: 
	$(CC) $(FLAGS) $(SEVER_SOURCE) -o $(SEVER_NAME)

clean:
	rm $(SEVER_NAME)
	rm $(CLIENT_NAME)
