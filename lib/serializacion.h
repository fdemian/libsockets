#include "sockets.h"

struct NIPC
{
  unsigned char Type;
  unsigned short int Length;
  void * Payload;
};

struct package serializePackage(struct NIPC messageToSerialize);
struct NIPC unserializePackage(void * serializedPackage);
