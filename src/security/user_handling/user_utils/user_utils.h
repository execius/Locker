#include "includes.h"

#ifndef USER_UTILS
#define USER_UTILS

int file_exists(const char *path, size_t path_maxlen);

int make_file_path(char *filepath, const char *path,
                   const char *filename, size_t str_maxlen);
int user_exists(const char *users_path,
                const char *username, size_t str_maxlen);
int directory_exists(const char *dir_name,
                     size_t str_maxlen);
#endif // !USER_UTILS
