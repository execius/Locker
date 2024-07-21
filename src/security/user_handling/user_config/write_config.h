#include "includes.h"

#ifndef WRITE_CFG 
#define WRITE_CFG

int write_user_configs(
  char *user_config_file ,
  pair **array_of_pairs,
  int number_of_configs,
  size_t str_maxlen,
  size_t line_maxlen,
  size_t path_maxlen
);


#endif // !EDIT_CFG
