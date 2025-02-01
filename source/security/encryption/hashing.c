#include "hashing.h"

int hashing_global(const char *password,
                   const unsigned char *salt, int salt_len,
                   int iterations, unsigned char *key,
                   int key_len,
                   const EVP_MD *(*hash_function)(void)) {
  if (!password || !salt || !key) {
    log_error("NULL in hashing_global function");
    return (errno = ERROR_NULL_VALUE_GIVEN);
  }
  (errno = PKCS5_PBKDF2_HMAC(
       password, strlen(password), salt, salt_len,
       iterations, hash_function(), key_len, key));
  switch (errno) {
  case LIBSSL_SUCCESS:
    return errno = SUCCESS;
    break;
  default:
    return errno;
    break;
  }
}
