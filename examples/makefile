#
# I hereby acknowledge that this makefile is a mess. 
# It will be fixed in the future, but I wouldn't hold my breath for too long. 
#
# Copyright (C) 2014 - Federico Caminiti
# 
# Copy & Paste the Two Clause BSD License here. 
#

FLAGS = -Werror -Wall -g -ggdb

CLIENT_SOURCE = sendRecieve_client.c 
CLIENT_NAME = simpleClient

SEVER_SOURCE = sendRecieve_server.c 
SEVER_NAME = simpleServer

SERIALIZED_CLIENT_SOURCE = sendRecieveSerialized_client.c
SERIALIZED_CLIENT_NAME   = serializedClient

SERIALIZED_SERVER_SOURCE = sendRecieveSerialized_server.c
SERIALIZED_SERVER_NAME   = serializedServer

all:	simple_client simple_server serialized_client serialized_server

simple_example:	simple_client simple_server

serializaton_example: serialized_client serialized_server

simple_client:
	$(CC) $(FLAGS) $(CLIENT_SOURCE) -o $(CLIENT_NAME)

simple_server: 
	$(CC) $(FLAGS) $(SEVER_SOURCE) -o $(SEVER_NAME)

serialized_client: 
	$(CC) $(FLAGS) $(SERIALIZED_CLIENT_SOURCE) -o $(SERIALIZED_CLIENT_NAME)

serialized_server:
	$(CC) $(FLAGS) $(SERIALIZED_SERVER_SOURCE) -o $(SERIALIZED_SERVER_NAME)

clean:
	rm $(SEVER_NAME)
	rm $(CLIENT_NAME)
	rm $(SERIALIZED_SERVER_NAME)
	rm $(SERIALIZED_CLIENT_NAME)
