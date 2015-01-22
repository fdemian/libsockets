Examples
========

This folder contains examples of how to use this library. These constitute client/server pairs. 

- sendRecieve_
    + client : sends data to the server, waits for a message from the server and once it arrives, prints it and then terminates.
    + server : waits for a client to send a message, prints it and then sends another message to the client. 

- sendRecieveSerialized_
    + client: serializes a string as a NIPC structure, sends it to the server and then waits for the server to send another message, serialized as a NIPC structure. It unserializes the message, prints it and terminates. 
    + server: waits for the client to send a message, unserializes it and prints it. It then sends a message to the client serialized as a NIPC structure.    
 
