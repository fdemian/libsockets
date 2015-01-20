int sendMessage(void * message, int type, int length, int socket)
{
  
  struct package packageToSend;
  struct NIPC dataToSerialize;

  dataToSerialize.Type = type;
  dataToSerialize.Length = length;
  dataToSerialize.Payload = message;

  packageToSend = serializePackage(dataToSerialize);
  
  if(send(socket, packageToSend.data, packageToSend.length, 0)== -1)
  {
    return ERROR_SEND;
  }

  free(packageToSend.data);

  return SUCCESS;
}
