#include "encryptdecrypt.h" 

int handleErrors(void) {
  ERR_print_errors_fp(stderr);
  return ERROR_LIBSSL_FAILURE;
}


int encrypt_aes256(const unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext){

  EVP_CIPHER_CTX *ctx;
  int len;

  // Create and initialize the context
  if (!(ctx = EVP_CIPHER_CTX_new())) return handleErrors();

  // Initialize the encryption operation
  if (LIBSSL_SUCCESS != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) return handleErrors();

  // Provide the message to be encrypted, and obtain the encrypted output
  if (LIBSSL_SUCCESS != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) handleErrors();

  // Finalize the encryption
  if (LIBSSL_SUCCESS != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) return handleErrors();

  // Clean up
  EVP_CIPHER_CTX_free(ctx);
  
  return SUCCESS;

}



int decrypt_aes256(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,unsigned char *iv, unsigned char *plaintext){
  EVP_CIPHER_CTX *ctx;

  int len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new()))
    handleErrors();

  /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
  if(LIBSSL_SUCCESS != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    return handleErrors();

  /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
  if(LIBSSL_SUCCESS != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    return handleErrors();

  /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
  if(LIBSSL_SUCCESS != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
    return handleErrors();

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return SUCCESS;
}
