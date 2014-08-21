struct NIPC
{
  unsigned char Type;
  unsigned short int Length;
  char* Payload;
};

struct Paquete
{
  char* Serializado;
  int Length;
};

struct Paquete Serializar(struct NIPC paqueteAserializar);
struct NIPC Deserializar(char* mensajeSerializado);
