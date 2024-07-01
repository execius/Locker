#include "includes.h"

#ifndef ENCRYPT_DECRYPT
#define ENCRYPT_DECRYPT
int encrypt_aes256(const unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);
int decrypt_aes256(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,unsigned char *iv, unsigned char *plaintext);
int handleErrors(void);
#endif // !ENCRYPT&DECRYPT
