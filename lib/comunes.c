int sendMessage(struct package dataToSend, int socket)
{
    
  if(send(socket, dataToSend.data, dataToSend.length, 0)== -1)
  {
    return ERROR_SEND;
  }
   
  return SUCCESS;
}
