#include "defined_values.h"

/*this function defines the paths to users and configs
 for a certain function*/
int define_paths(char *Locker_folder, char *users_folder,
                 char *configs_folder,
                 char *accounts_folder, size_t maxlen,
                 char *PWD) {

  char *temp_Locker_folder =
      malloc(get_system_max_path() * sizeof(char));
  if (SUCCESS != make_file_path(temp_Locker_folder, PWD,
                                ".Locker", maxlen))
    goto end;
  if (NULL != Locker_folder)
    strncpy(Locker_folder, temp_Locker_folder,
            get_system_max_path());
  if (NULL != configs_folder)
    if (SUCCESS != make_file_path(configs_folder,
                                  temp_Locker_folder,
                                  "configs", maxlen))
      goto end;
  if (NULL != users_folder)
    if (SUCCESS != make_file_path(users_folder,
                                  temp_Locker_folder,
                                  "users", maxlen))
      goto end;

  if (NULL != accounts_folder)
    if (SUCCESS != make_file_path(accounts_folder,
                                  temp_Locker_folder,
                                  "accounts", maxlen))
      goto end;

end:
  if (temp_Locker_folder)
    free(temp_Locker_folder);
  return errno;
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
