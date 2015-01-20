struct NIPC
{
  unsigned char Type;
  unsigned short int Length;
  void * Payload;
};


struct package
{
  void * data;
  int length;
};

struct package serializePackage(struct NIPC messageToSerialize);
struct NIPC unserializePackage(void * serializedPackage);
