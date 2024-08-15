#include "user_utils.h"

/*makes a file path from a path and a filename*/
int make_file_path(char *filepath
                   ,const char *path
                   ,const char *filename
                   ,size_t str_maxlen){
  switch (path[strnlen(path,str_maxlen)-1]) {
    case 47: 
      sprintf(filepath, "%s%s",path,filename);
      if ( errno  < 0){
        errno = ERROR_STDLIB_FUNTION_FAILURE;
      return errno;
      break;}
    default:
      sprintf(filepath, "%s/%s",path,filename);
      if ( errno  < 0){
        errno = ERROR_STDLIB_FUNTION_FAILURE;
      return errno;
      break;}
  }
  return errno = SUCCESS;
}

/*checks if a file exists using access check*/
int file_exists(const char *path , size_t path_maxlen)
{
  if (!path)
    return errno = ERROR_NULL_VALUE_GIVEN;
  /*if file doesnt exist*/
  if (access(path, F_OK) == -1){
    errno = ERROR_FILE_DOESNT_EXIST;
    return errno;
  }
  return errno = SUCCESS;
}

/*checking if a user exists by checking if the user 
  has a file in the dirctory of users*/
int user_exists(const char *users_path,
                const char *username,
                size_t str_maxlen){
  char pathtofile[2*str_maxlen];
  /*making  the path to the file like .../userdirect/username*/
  if ( SUCCESS != make_file_path(
    pathtofile,users_path,username,str_maxlen))
    return errno;

  if(SUCCESS != file_exists(pathtofile,
                                   2*str_maxlen)){
    errno = ERROR_USER_DOESNT_EXIST;
    return errno;
  }
  return SUCCESS;
}

int directory_exists(const char *dir_name,
                     size_t str_maxlen)
{
  /*checking the str lenght is in limits*/
  if('\0' != dir_name[strnlen(dir_name,str_maxlen)]){
    log_error("eror in funtion directory_exists");
    errno = ERROR_TOO_LONG_STRING;
    return errno;
  }
  /*check for NULLs*/
  if (!dir_name){
    log_error("eror in funtion directory_exists");
    errno = ERROR_NULL_VALUE_GIVEN;
    return errno;
  }

  struct stat info;

  // Check if stat succeeds and if the path is a directory
  if (stat(dir_name , &info) == 0 && S_ISDIR(info.st_mode)) {
    return errno = SUCCESS; // Directory exists
  } 
  switch (errno) {
    case ENOENT:
      errno = ERROR_DIRECTORY_DOESNT_EXIST;
      return errno;
      break;
    default:
      perror("stat");
      errno = ERROR_STDLIB_FUNTION_FAILURE;
      return errno;
      break;
  }
}
