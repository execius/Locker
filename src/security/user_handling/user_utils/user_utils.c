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
int file_exists(const char *path , size_t path_maxlen)
{
  assert(path);
  /*if file doesnt exist*/
  if (access(path, F_OK) == -1)
    return ERROR_FILE_DOESNT_EXIST;

  return SUCCESS;
}

/*checking if a user exists by checking if the user 
  has a file in the dirctory of users*/
int user_exists(const char *users_path,
                const char *username,
                size_t str_maxlen){
  int err = 0;
  char pathtofile[2*str_maxlen];
  /*making  the path to the file like .../userdirect/username*/
  if ( SUCCESS != (err = make_file_path(
    pathtofile,users_path,username,str_maxlen)))
    return err;

  if(SUCCESS != (err = file_exists(pathtofile,
                                   2*str_maxlen)))
    return err;

  return SUCCESS;
}

int directory_exists(const char *dir_name,
                     size_t str_maxlen)
{
  /*checking the str lenght is in limits*/
  if('\0' != dir_name[strnlen(dir_name,str_maxlen)]){
    log_error("eror in funtion directory_exists");
    return ERROR_TOO_LONG_STRING;
  }
  /*check for NULLs*/
  if (!dir_name){
    log_error("eror in funtion directory_exists");
      return ERROR_NULL_VALUE_GIVEN;
  }

  struct stat info;

  // Check if stat succeeds and if the path is a directory
  if (stat(dir_name , &info) == 0 && S_ISDIR(info.st_mode)) {
    return SUCCESS; // Directory exists
  } 
  switch (errno) {
    case ENOENT:
      log_error("directory doesnt exist");
      return ERROR_DIRECTORY_DOESNT_EXIST;
      break;
    default:
      perror("stat");
      return ERROR_STDLIB_FUNTION_FAILURE;
      break;
  }
}
