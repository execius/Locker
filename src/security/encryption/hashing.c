#include "hashing.h"


int hash_sha256(
  const char *password,
  unsigned char *salt,
  unsigned char *hash) 
{
  EVP_MD_CTX *mdctx;
  if (!(mdctx = EVP_MD_CTX_new()))
    return  errno = handleErrors();

  // Initialize the context with the hash function
  if (1 != EVP_DigestInit_ex(
            mdctx,
            EVP_sha256(),
            NULL))
    return errno = handleErrors();

  // Add the salt
  if (1 != EVP_DigestUpdate(
            mdctx,
            salt,
            SHA256_SALT_SIZE)) 
    return errno = handleErrors();

  // Add the password
  if (1 != EVP_DigestUpdate(
            mdctx,
            password,
            strlen(password))) 
    return errno = handleErrors();

  // Finalize the hash
  unsigned int len;
  if (1 != EVP_DigestFinal_ex(
            mdctx,
            hash,
            &len))
    return errno = handleErrors();

  // Clean up
  EVP_MD_CTX_free(mdctx);
  return errno = SUCCESS;
}

int hashing_global(const char *password,
               const unsigned char *salt,
               int salt_len,
               int iterations,
               unsigned char *key,
               int key_len,
               const EVP_MD *(*hash_function)(void)) {
  if(!password || !salt || !key){
    log_error("NULL in hashing_global function");
    return (errno = ERROR_NULL_VALUE_GIVEN);
  }
  (errno = PKCS5_PBKDF2_HMAC(
    password, 
    strlen(password),
    salt, 
    salt_len,
    iterations,
    hash_function(),
    key_len,
    key));
  switch (errno) {
    case LIBSSL_SUCCESS :
      return SUCCESS;
      break;
    default:
      return errno;
      break;
  }
}

