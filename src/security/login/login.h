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
          size_t hex_salt_maxlen);

int binary_to_hex(const unsigned char *bin
    , size_t len
    , unsigned char *hex);

int hex_to_binary(const char *hex,
    unsigned char *bin,
    size_t bin_len);
#endif // !LOGIN
