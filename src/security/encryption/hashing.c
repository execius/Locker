#include "hashing.h"


int hash_sha256(
  const char *password,
  unsigned char *salt,
  unsigned char *hash) 
{
  EVP_MD_CTX *mdctx;
  if (!(mdctx = EVP_MD_CTX_new()))
    return  handleErrors();

  // Initialize the context with the hash function
  if (1 != EVP_DigestInit_ex(
            mdctx,
            EVP_sha256()
            NULL))
    return handleErrors();

  // Add the salt
  if (1 != EVP_DigestUpdate(
            mdctx,
            salt,
            SHA256_SALT_SIZE)) 
    return handleErrors();

  // Add the password
  if (1 != EVP_DigestUpdate(
            mdctx,
            password,
            strlen(password))) 
    return handleErrors();

  // Finalize the hash
  unsigned int len;
  if (1 != EVP_DigestFinal_ex(
            mdctx,
            hash,
            &len))
    return handleErrors();

  // Clean up
  EVP_MD_CTX_free(mdctx);
  return SUCCESS;
}
