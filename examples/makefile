FLAGS = -Werror -Wall -g -ggdb

SEVER_SOURCE = sendRecieve_server.c 
SEVER_NAME = simpleServer

CLIENT_SOURCE = sendRecieve_client.c 
CLIENT_NAME = simpleClient

SERIALIZED_SERVER_SOURCE = sendRecieveSerialized_server.c
SERIALIZED_SERVER_NAME   = serializedServer

SERIALIZED_CLIENT_SOURCE = sendRecieveSerialized_client.c
SERIALIZED_CLIENT_NAME   = serializedClient

all:	simple_client simple_server serialized_client serialized_server

simple_example:	simple_client simple_server

serializaton_example: serialized_client serialized_server

simple_client:
	$(CC) $(FLAGS) $(CLIENT_SOURCE) -o $(CLIENT_NAME)

simple_server: 
	$(CC) $(FLAGS) $(SEVER_SOURCE) -o $(SEVER_NAME)

serialized_client: 
	$(CC) $(FLAGS) $(SENDREC_CLIENT_SOURCE) -o $(SENDREC_CLIENT_NAME)

serialized_server:
	$(CC) $(FLAGS) $(SENDREC_SERVER_SOURCE) -o $(SENDREC_SERVER_NAME)

clean:
	rm $(SEVER_NAME)
	rm $(CLIENT_NAME)
	rm $(SERIALIZED_SERVER_NAME)
	rm $(SERIALIZED_CLIENT_NAME)
