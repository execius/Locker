#include "includes.h"

#ifndef LOGIN
#define LOGIN
int login(const char *users_path,
          const char *input_username,
          const char *input_password,
          size_t username_maxlen,
          size_t str_maxlen,
          size_t hash_maxlen,
          size_t salt_maxlen);

#endif // !LOGIN
