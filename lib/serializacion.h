struct NIPC
{
  unsigned char Type;
  unsigned short int Length;
  char* Payload;
};

struct NIPCBin
{
  unsigned char Type;
  unsigned short int Length;
  void* Payload;
};

struct Paquete
{
  char* Serializado;
  int Length;
};

struct PaqueteBinario
{
  void * Serializado;
  int Length;
};


struct Paquete Serializar(struct NIPC paqueteAserializar);
struct PaqueteBinario SerializarBinario(struct NIPCBin paqueteAserializar);
struct NIPC Deserializar(char* mensajeSerializado);
struct NIPCBin DeserializarBinario(void * mensajeSerializado);
