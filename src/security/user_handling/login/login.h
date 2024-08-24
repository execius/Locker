#include "includes.h"

#ifndef LOGIN
#define LOGIN
int login(char *users_path,
          char *input_username,
          char *input_password,
          size_t str_maxlen,
          size_t hash_maxlen,
          size_t salt_maxlen,
          size_t Hex_hash_maxlen,
          size_t hex_salt_maxlen,
          const EVP_MD *(*hash_function)(void)
          );

#endif // !LOGIN
