#include "serializacion.h"

struct Paquete Serializar(struct NIPC paqueteAserializar)
{

  struct Paquete mensajeSerializado;
  __int32_t tamanoPaquete = 0;
  char * str;

  tamanoPaquete = sizeof(char) + sizeof(char) + sizeof(char) + sizeof(unsigned short int)+ sizeof(char) + paqueteAserializar.Length;
  mensajeSerializado.Length = tamanoPaquete;
  mensajeSerializado.Serializado = malloc(sizeof(char) * mensajeSerializado.Length);

  memset(mensajeSerializado.Serializado, 0, 1); // Copio el primer 0 de control.
  memcpy(mensajeSerializado.Serializado+1, &(paqueteAserializar.Type), 1); // Copio el tipo.
  memset(mensajeSerializado.Serializado+1+sizeof(paqueteAserializar.Type), 0, 1); // Copio el segundo 0 de control.
  memcpy(mensajeSerializado.Serializado+2+sizeof(paqueteAserializar.Type), &(paqueteAserializar.Length), 2); // Copio la longitud del Payload.
  memset(mensajeSerializado.Serializado+2+sizeof(paqueteAserializar.Type)+sizeof(paqueteAserializar.Length), 0, 1); // Copio el tercer 0 de control.

  // Copio el payload.
  if(paqueteAserializar.Length > 0)
  {
    str = mensajeSerializado.Serializado + 3 + sizeof(paqueteAserializar.Type) + sizeof(paqueteAserializar.Length);
    memcpy(str, paqueteAserializar.Payload, paqueteAserializar.Length); 
  }

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
