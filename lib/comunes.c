int mandarMensaje(char * mensaje, int tipoMensaje, int socket)
{
  struct Paquete recibido;
  struct NIPC paqueteAMandar;

  paqueteAMandar.Type = tipoMensaje;
  paqueteAMandar.Length = strlen(mensaje);
  paqueteAMandar.Payload = mensaje;

  recibido = Serializar(paqueteAMandar);

  if(send(socket, recibido.Serializado, recibido.Length, 0)== -1)
  {
    return ERROR_SEND;
  }

  free(recibido.Serializado);

  return SUCCESS;
}

int mandarMensajeBinario(void * mensaje, int tipoMensaje, int largo, int socket)
{
		
  struct PaqueteBinario recibido;
  struct NIPCBin paqueteAMandar;

  paqueteAMandar.Type = tipoMensaje;
  paqueteAMandar.Length = largo;
  paqueteAMandar.Payload = mensaje;

  recibido = SerializarBinario(paqueteAMandar);
  
  if(send(socket, recibido.Serializado, recibido.Length, 0)== -1)
  {
    return ERROR_SEND;
  }

  //free(recibido.Serializado);

  return SUCCESS;
}
