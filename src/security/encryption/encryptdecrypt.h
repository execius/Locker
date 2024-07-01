#include "includes.h"

#ifndef ENCRYPT_DECRYPT
#define ENCRYPT_DECRYPT
int encrypt_aes256(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext,int *ciphertext_len);
int decrypt_aes256(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,unsigned char *iv, unsigned char *plaintext,int *plaintext_len);
int handleErrors(void);
#endif // !ENCRYPT&DECRYPT
