#include "serializacion.h"

struct Paquete Serializar(struct NIPC paqueteAserializar)
{
	struct Paquete mensajeSerializado;
	__int32_t tamanoPaquete = 0;

	tamanoPaquete = sizeof(char) + sizeof(char) + sizeof(char) + sizeof(unsigned short int)+ sizeof(char) + paqueteAserializar.Length;
	mensajeSerializado.Length = tamanoPaquete;
	mensajeSerializado.Serializado = (char*) malloc((sizeof(char) * mensajeSerializado.Length));

	memset(mensajeSerializado.Serializado, 0, 1); // copio el primer 0 de control
	memcpy(mensajeSerializado.Serializado+1, &(paqueteAserializar.Type), 1); // copio el type
	memset(mensajeSerializado.Serializado+1+sizeof(paqueteAserializar.Type), 0, 1); // copio el segundo 0 de control
	memcpy(mensajeSerializado.Serializado+2+sizeof(paqueteAserializar.Type), &(paqueteAserializar.Length), 2); // copio el Length del Payload
	memset(mensajeSerializado.Serializado+2+sizeof(paqueteAserializar.Type)+sizeof(paqueteAserializar.Length), 0, 1); // copio el tercer 0 de control

	// copio el payload
	if(paqueteAserializar.Length > 0)
		memcpy(mensajeSerializado.Serializado+3+sizeof(paqueteAserializar.Type)+sizeof(paqueteAserializar.Length), paqueteAserializar.Payload, paqueteAserializar.Length); 

	return mensajeSerializado;
}

struct NIPC Deserializar(char* mensajeSerializado)
{
	struct NIPC mensajeDeserializado;

	memcpy(&(mensajeDeserializado.Type), mensajeSerializado+1, 1);
	memcpy(&(mensajeDeserializado.Length),mensajeSerializado+3, sizeof(mensajeDeserializado.Length));

	if (mensajeDeserializado.Length>0)
	{
		mensajeDeserializado.Payload = calloc(1, mensajeDeserializado.Length + 1);
		strncpy( mensajeDeserializado.Payload, mensajeSerializado + 6, mensajeDeserializado.Length );
	}

	return mensajeDeserializado;
}

