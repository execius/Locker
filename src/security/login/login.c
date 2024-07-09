#include "login.h"
static int compare_creds(const char *credential ,
                         const char *userinput,
                         size_t len){

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

static int user_exists(const char *users_path,
                       const char *usrname,
                       size_t str_maxlen){
  
  char pathtofile[2*str_maxlen];
  strncat(pathtofile,users_path,str_maxlen);
  strncat(pathtofile,usrname,str_maxlen);
  if(SUCCESS != file_exists(pathtofile)){
    log_error("no such user exists");
    return ERROR_USER_DOESNT_EXIST;
  }
  return SUCCESS;
}

int get_salt_nd_hashedpass(const char *users_files,
                           const char *username,
                           unsigned char *hashed_password,
                           unsigned char *salt,
                           size_t str_maxlen,
                           size_t hash_maxlen,
                           size_t salt_maxlen){
  
  int err = 0;
  FILE *file;
  int tracker = 0;
  char line[hash_maxlen]
  char pathtofile[2*str_maxlen];

  strncat(pathtofile,users_path,str_maxlen);
  strncat(pathtofile,usrname,str_maxlen);

  if(SUCCESS =! file_exists(pathtofile))
    return ERROR_FILE_DOESNT_EXIST;

  if (NULL == (file = fopen(pathtofile,"r"))){
    log_error("eror while retrieving hashed password from file ,file exists but cannot be read");
    return ERROR_CANNOT_READ_FILE;
  }

  while (fgets(line,file)&& tracker++ < 2){
    switch (tracker) {
      case 0:
        strncat(hashed_password,line,hash_maxlen);
        break;
      case 1:
        strncat(salt,line,salt_maxlen);
        break;
    }
  }
  if(2 == tracker){
    log_error("eror while retrieving salt and hashed password ,invalid user file");
    return ERROR_INVALID_USER_FILE;}
  
  return SUCCESS;
}

int login(const char *users_files,
          const char *input_username,
          const char *input_password,
          size_t username_maxlen,
          size_t str_maxlen,
          size_t hash_maxlen,
          size_t salt_maxlen){
  int err = 0;

  if(strnlen(input_password,maxlen+1) >= str_maxlen  ||
    strnlen(input_username,maxlen+1) >= str_maxlen  ||
    strnlen(users_files,maxlen+1) >= str_maxlen )

    return ERROR_TOO_LONG_STRING;
  if (!users_path || !input_username || !input_password ){
    log_error("null string given , in funtion : login")
  }

  if(SUCCESS != user_exists(users_path,input_username)){
    return ERROR_USER_DOESNT_EXIST;
  }

  unsigned char input_password_hash [hash_maxlen];
  unsigned char user_password_hash [hash_maxlen];
  unsigned char salt [salt_maxlen];

  if(SUCCESS =! (err = get_salt_nd_hashedpass
    (users_files,username,
     user_password_hash,
     salt,str_maxlen,
     hash_maxlen,
     salt_maxlen))){
    log_error("could not get salt and hashed user password");
    return err;
  }

  if (SUCCESS != (err = hash_sha256(input_password,salt,
  ERROR_INCORRECT_PASSWORD = -22,
                                    input_password_hash))){
    return err;}

  if(SUCCESS != (err = compare_creds(input_password_hash,
                              user_password_hash,
                              hash_maxlen))){
    log_error("login error,incorrect password");
    return err;
  }
  return SUCCESS;
}

