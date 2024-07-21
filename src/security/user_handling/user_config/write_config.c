#include "write_config.h"


int write_user_configs(
  char *user_config_file ,
  pair **array_of_pairs,
  int number_of_configs,
  size_t str_maxlen,
  size_t line_maxlen,
  size_t path_maxlen
){
  int i = 0;
  while (i++ < number_of_configs) {

    if (SUCCESS != write_config_pair(
      user_config_file,
      *(array_of_pairs+i),
      str_maxlen,
      line_maxlen,
      path_maxlen
    ))
    return  errno;
    }
  return SUCCESS;
}


