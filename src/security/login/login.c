#include "login.h"
static int compare_creds(const char *credential ,const char *userinput,size_t len){
  int err;
  if (0 != strncmp(credential,userinput,len))
    return ERROR_INVALID_CREDENTIALS;
  return SUCCESS;
 }

int file_exists(const char *path)
{
    /*if file doesnt exist*/
    if (access(path, F_OK) == -1)
        return ERROR_FILE_DOESNT_EXIST;

    return SUCCESS;
}

static int user_exists(const char *users_path,const char *usrname,size_t str_maxlen){
  char pathtofile[2*maxlen];
  strncat(pathtofile,users_path,str_maxlen);
  strncat(pathtofile,usrname,str_maxlen);
  if(SUCCESS != file_exists(pathtofile)){
    log_error("no such user exists");
    return ERROR_USER_DOESNT_EXIST;
  }
  return SUCCESS;
}

int login(const char *users_files,const char *input_username,const char *input_password,char *salt,size_t username_maxlen,size_t password_maxlen){
  if (!users_path || !input_username || !input_password ){
    log_error("null string given , in funtion : login")
  }
  if(SUCCESS != user_exists(users_path,input_username)){
    return ERROR_USER_DOESNT_EXIST;
  }
  char *input_password_hash = malloc(sizeof(char))
}

