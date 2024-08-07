#include "defined_values.h"



/*this function defines the paths to users and configs
 for a certain function*/
int define_paths(char *Locker_folder,
                 char *users_folder,
                 char *configs_folder,
                 size_t maxlen,
                 char *PWD)
{
  int err = 0;

  if(SUCCESS!= (err= 
    make_file_path(
      configs_folder,PWD,
      ".Locker/configs",
      maxlen
    )))
    return err;
  if(SUCCESS!= (err= 
    make_file_path(
      Locker_folder,PWD,
      ".Locker",
      maxlen
    )))
    return err;

  if(SUCCESS!= (err= 
    make_file_path(
      users_folder,PWD,
      ".Locker/users",
      maxlen
    )))
    return err;

  
  return SUCCESS;

}
