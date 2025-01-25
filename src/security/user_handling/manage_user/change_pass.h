#include "includes.h"

#ifndef CHNG_PASS
#define CHNG_PASS

int change_pass(char *users_directory, char *password,
                char *username, size_t str_maxlen,
                size_t bin_hash_len, size_t bin_salt_len,
                size_t hex_hash_len, size_t hex_salt_len,
                const EVP_MD *(*hash_function)(void));

#endif // !CHNG_PASS
#define CHNG_PASS
