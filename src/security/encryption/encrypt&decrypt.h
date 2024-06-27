#include "includes.h"

#ifndef ENCRYPT&DECRYPT
#define ENCRYPT&DECRYPT
int encrypt_aes256(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);
int decrypt_aes256(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,unsigned char *iv, unsigned char *plaintext);
void handleErrors();
#endif // !ENCRYPT&DECRYPT
