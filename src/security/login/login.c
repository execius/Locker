#include "login.h"
/*makes a file path from a path and a filename*/
static int make_file_path(char *filepath
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

int binary_to_hex(const unsigned char *bin,
                  size_t len,
                  unsigned char *hex) {

    for (size_t i = 0; i < len; i++) {
        sprintf((char *)(hex + (i * 2)), "%02x", bin[i]);
    }
    hex[len * 2] = '\0';
  return SUCCESS;
}

int hex_to_binary(const char *hex,
                  unsigned char *bin, 
                  size_t bin_len) {

    for (size_t i = 0; i < bin_len; i++) {
        sscanf(hex + (i * 2), "%02x",(unsigned int *) &bin[i]);
    }
  return SUCCESS;
}

/*compares two binary credentials */
static int compare_creds(const char *credential ,
                         const char *userinput,
                         size_t len){

  if (0 != CRYPTO_memcmp(credential,userinput,len))
    return ERROR_INVALID_CREDENTIALS;
  return SUCCESS;
 }
/*checks if a file exists using access check*/
int file_exists(const char *path)
{
    /*if file doesnt exist*/
    if (access(path, F_OK) == -1)
        return ERROR_FILE_DOESNT_EXIST;

    return SUCCESS;
}
/*checking if a user exists by checking if the user 
  has a file in the directory of users*/
static int user_exists(const char *users_path,
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
/*fetches a salt and a hashed password from a user file*/
int get_salt_nd_hashedpass(const char *users_path,
                           const char *username,
                           char *hex_hashed_password,
                           char *hex_salt,
                           size_t str_maxlen,
                           size_t hex_hash_maxlen,
                           size_t hex_salt_maxlen){
  /*to track errors*/
  int err = 0;  
  /*user file*/
  FILE *file;  
  char pathtofile[2*str_maxlen];
  /*making  the path to the file like .../userdirect/username*/
  if ( SUCCESS != (err = make_file_path(
    pathtofile,users_path,username,str_maxlen)))
    return err;
  
  /*check that the file exists*/
  if(SUCCESS !=(err = file_exists(pathtofile)))
    return err;
  /*open file and check for errors*/
  if (NULL == (file = fopen(pathtofile,"r"))){
    log_error("eror while retrieving hashed password from file ,file exists but cannot be read\n");
    return ERROR_CANNOT_READ_FILE;
  }

  if (NULL == fgets(hex_salt,
                    hex_salt_maxlen,
                    file) ||
    NULL == fgets(hex_hashed_password,
                  hex_hash_maxlen,
                  file) 
  ) {

    log_error("An error occurred reading the file\n");
    fclose(file);
    return ERROR_STDLIB_FUNTION_FAILURE;
  }
  fclose(file);
  return SUCCESS;
}

int login(char *users_path,
          char *input_username,
          char *input_password,
          size_t str_maxlen,
          size_t hash_maxlen,
          size_t salt_maxlen,
          size_t hex_hash_maxlen,
          size_t hex_salt_maxlen){
  /*removing newline character*/
  // input_username[strcspn(input_username, "\n")] =  '\0';
  // input_password[strcspn(input_password, "\n")] =  '\0';
  // users_path[strcspn(users_path, "\n")] = '\0';
  //

  unsigned char input_password_hash [hash_maxlen];
  unsigned char user_password_hash [hash_maxlen];
  unsigned char salt [salt_maxlen];
  char hex_salt[hex_salt_maxlen];
  char hex_hash[hex_hash_maxlen];

  int err = 0;
  /*check for null pointers*/
  if (!users_path || !input_username || !input_password ){
    log_error("null string given , in funtion : login");
  }

/*check the langhts of strings given*/
  if(strnlen(input_password,str_maxlen) >= str_maxlen  ||
    strnlen(input_username,str_maxlen) >= str_maxlen  ||
    strnlen(users_path,str_maxlen) >= str_maxlen )

    return ERROR_TOO_LONG_STRING;
 /*check that theres a file with the same name as the user
  * this validates if the user is existent*/
  if(SUCCESS != user_exists(users_path,
                            input_username,
                            str_maxlen)){

    return ERROR_USER_DOESNT_EXIST;
  }

  /*getting the hash and salt from the user file*/
  if(SUCCESS != (err = get_salt_nd_hashedpass
    (users_path,input_username,
     hex_hash,
     hex_salt,str_maxlen,
     hex_hash_maxlen,
     hex_salt_maxlen))){
    log_error("could not get salt and hashed user password");
    return err;
  }
    /* Remove newline characters*/
  hex_salt[strcspn(hex_salt, "\n")] = '\0';
  hex_hash[strcspn(hex_hash, "\n")] = '\0';

/*converting hex hash and salt to binary for comparison*/
  hex_to_binary(hex_salt,
                salt,
                salt_maxlen);
  hex_to_binary(hex_hash,
                user_password_hash,
                hash_maxlen);

  /*hashing the inserted password to compare it to the user password hash*/
  if (SUCCESS != 
    (err = hash_sha256(
      input_password,salt,
      input_password_hash))){

    return err;}
  /*comparison*/
  if(SUCCESS != (err = compare_creds(
    (const char *)input_password_hash,
    (const char *)user_password_hash
    ,hash_maxlen))){
    log_error("login error,incorrect password");
    return err;
  }
  return SUCCESS;
}

