#include "includes.h"


#ifndef HASH
#define HASH
int hash_sha256(
    const char *password,
    unsigned char *salt,
    unsigned char *hash);

int hashing_global(const char *password,
               const unsigned char *salt,
               int salt_len,
               int iterations,
               unsigned char *key,
               int key_len,
               const EVP_MD *(*hash_function)(void)) ;
#endif // !HASH
