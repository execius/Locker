#include "includes.h"

#ifndef ENCRYPT_DECRYPT
#define ENCRYPT_DECRYPT


int encrypt(const unsigned char *plaintext,
                   int plaintext_len,
                   unsigned char *key,
                   unsigned char *iv,
                   unsigned char *ciphertext,
                   const EVP_CIPHER * (*EVP_CBC_FUNC)(void);




int decrypt(unsigned char *ciphertext,
                   int ciphertext_len,
                   unsigned char *key,
                   unsigned char *iv,
                   unsigned char *plaintext,
                   const EVP_CIPHER * (*EVP_CBC_FUNC)(void)
int handleErrors(void);

#endif // !ENCRYPT&DECRYPT
