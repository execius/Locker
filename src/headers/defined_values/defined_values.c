#include "defined_values.h"


const char *list_of_wanted_inf[] = {"encryption"};
int define_paths(char *users_folder,
                 char *configs_folder,
                 size_t maxlen,
                 char *PWD)
{
  make_file_path(
    configs_folder,PWD,
    ".Locker/configs",
    maxlen
  );
  if(SUCCESS!= errno )
    return errno;
  make_file_path(
    users_folder,PWD,
    ".Locker/users",
    maxlen
  );
  if(SUCCESS!= errno )
    return errno;

  return SUCCESS;

}
