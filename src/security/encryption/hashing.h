#include "includes.h"


#ifndef HASH
#define HASH
int hash_sha256(const char *password, unsigned char *salt, unsigned char *hash);
#endif // !HASH
