#include "includes.h"

#ifndef MAKE_USER
#define MAKE_USER
int make_user(char *users_files_path, char *password,
              char *username, size_t str_maxlen,
              size_t bin_hash_len, size_t bin_salt_len,
              size_t hex_hash_len, size_t hex_salt_maxlen,
              const EVP_MD *(*hash_function)(void));

#endif // !MAKE_USER
