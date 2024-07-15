#include "user_utils.h"

/*makes a file path from a path and a filename*/
int make_file_path(char *filepath
                          ,const char *path
                          ,const char *filename
                          ,size_t str_maxlen){
  size_t check;
  switch (path[strnlen(path,str_maxlen)-1]) {
    case 47:
      if ((check = sprintf(
        filepath, "%s%s", 
        path,filename))  < 0)
        return ERROR_STDLIB_FUNTION_FAILURE;
      break;
    default:
      if (
        (check = sprintf(
          filepath, "%s/%s"
          ,path,filename))   < 0)
        return ERROR_STDLIB_FUNTION_FAILURE;
    break;
  }
  return SUCCESS;
}

/*checks if a file exists using access check*/
static int file_exists(const char *path)
{
    /*if file doesnt exist*/
    if (access(path, F_OK) == -1)
        return ERROR_FILE_DOESNT_EXIST;

    return SUCCESS;
}

/*checking if a user exists by checking if the user 
  has a file in the directory of users*/
int user_exists(const char *users_path,
                       const char *username,
                       size_t str_maxlen){
  int err ;
  char pathtofile[2*str_maxlen];
  /*making  the path to the file like .../userdirect/username*/
  if ( SUCCESS != (err = make_file_path(
    pathtofile,users_path,username,str_maxlen)))
    return err;

  if(SUCCESS != file_exists(pathtofile)){
    log_error("no such user exists");
return ERROR_USER_DOESNT_EXIST;
  }
  return SUCCESS;
}

