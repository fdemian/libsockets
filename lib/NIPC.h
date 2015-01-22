#include "sockets.h"

struct NIPC
{
  unsigned char Type;
  unsigned short int Length;
  void * Payload;
};

struct package NIPC_serialize(struct NIPC messageToSerialize);
struct NIPC NIPC_unserialize(void * serializedPackage);
