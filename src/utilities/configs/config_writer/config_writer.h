#include "includes.h"

#ifndef CFG_WRITER
#define CFG_WRITER
int make_config_line(
    char *line,
    char *key,
    char* value,
    size_t str_maxlen
    );
int write_config_line(char *config_file,
    char *line
    ,size_t line_maxlen
    ,size_t path_maxlen);

int write_config_pair(
    char *config_file,
    pair *couple,
    size_t str_maxlen,
    size_t line_maxlen,
    size_t path_maxlen);
int write_user_configs(
  char *user_config_file ,
  pair **array_of_pairs,
  int number_of_configs,
  size_t str_maxlen,
  size_t line_maxlen,
  size_t path_maxlen
);

#endif // !CFG_WRITER'
