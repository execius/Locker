#include "defined_values.h"

/*this function defines the paths to users and configs
 for a certain function*/
int define_paths(char *Locker_folder, char *users_folder,
                 char *configs_folder,
                 char *accounts_folder, size_t maxlen,
                 char *PWD) {
  if (NULL != configs_folder)
    if (SUCCESS != make_file_path(configs_folder, PWD,
                                  ".Locker/configs",
                                  maxlen))
      return errno;
  if (NULL != Locker_folder)
    if (SUCCESS != make_file_path(Locker_folder, PWD,
                                  ".Locker", maxlen))
      return errno;
  if (NULL != users_folder)
    if (SUCCESS != make_file_path(users_folder, PWD,
                                  ".Locker/users", maxlen))
      return errno;

  if (NULL != accounts_folder)
    if (SUCCESS != make_file_path(accounts_folder, PWD,
                                  ".Locker/accounts",
                                  maxlen))
      return errno;

  return errno = SUCCESS;
}
size_t get_system_max_path(void) {
#ifdef _WIN32
  return DEFAULT_MAX_PATH;
#else
  long max_path = pathconf("/", _PC_PATH_MAX);
  return (max_path > 0) ? (size_t)max_path
                        : DEFAULT_MAX_PATH;
#endif
}
