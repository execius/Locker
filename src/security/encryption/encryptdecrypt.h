#include "includes.h"

#ifndef ENCRYPT_DECRYPT
#define ENCRYPT_DECRYPT


int encrypt_aes256(const unsigned char *plaintext,
                   int plaintext_len,
                   unsigned char *key,
                   unsigned char *iv,
                   unsigned char *ciphertext);



int decrypt_aes256(unsigned char *ciphertext,
                   int ciphertext_len,
                   unsigned char *key,
                   unsigned char *iv,
                   unsigned char *plaintext);

int derive_key(const char *password,
               const unsigned char *salt,
               int salt_len,
               int iterations,
               unsigned char *key,
               int key_len);
int handleErrors(void);

#endif // !ENCRYPT&DECRYPT
