#include "NIPC.h"

/*
 * Serialize a NIPC structure into a package that has the following structure. 
 * 
 * 0 - Type - 0 - Payload Length - 0 - Payload.
 * 
 */
struct package NIPC_serialize(struct NIPC messageToSerialize)
{

  struct package serializedPackage;
  __int32_t packageSize = 0;
  void * str;
    
  packageSize = sizeof(char) + sizeof(char) + sizeof(char) + sizeof(unsigned short int)+ sizeof(char) + messageToSerialize.Length;
  serializedPackage.length = packageSize;
  serializedPackage.data = malloc(sizeof(char) * packageSize);

  memset(serializedPackage.data, 0, 1);
  memcpy(serializedPackage.data+1, &(messageToSerialize.Type), 1);
  memset(serializedPackage.data+1+sizeof(messageToSerialize.Type), 0, 1);
  memcpy(serializedPackage.data+2+sizeof(messageToSerialize.Type), &(messageToSerialize.Length), 2);
  memset(serializedPackage.data+2+sizeof(messageToSerialize.Type)+sizeof(messageToSerialize.Length), 0, 1);
  
  if(messageToSerialize.Length > 0)
  {
    str = serializedPackage.data + 3 + sizeof(messageToSerialize.Type) + sizeof(messageToSerialize.Length);
    memcpy(str, messageToSerialize.Payload, messageToSerialize.Length); 
  }
  
  return serializedPackage;
}


/*
 * Unserialize a package that has the following structure: 
 * 0 - Type - 0 - Payload Length - 0 - Payload.
 * 
 * The function returns a NIPC structure.  
 */
struct NIPC NIPC_unserialize(void * serializedPackage)
{
  struct NIPC unserializedMessage;

  memcpy(&(unserializedMessage.Type), serializedPackage+1, 1);
  memcpy(&(unserializedMessage.Length),serializedPackage+3, sizeof(unserializedMessage.Length));

  if (unserializedMessage.Length > 0)
  {
    unserializedMessage.Payload = calloc(1, unserializedMessage.Length + 1);
    memcpy(unserializedMessage.Payload, serializedPackage + 6, unserializedMessage.Length);
  }

  return unserializedMessage;
}
