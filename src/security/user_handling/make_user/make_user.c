#include "make_user"

int make_user(
    char *users_directory,
    char *password,
    char *username,
    size_t str_maxlen,
    size_t bin_hash_len,
    size_t bin_salt_len,
    size_t hex_hash_len,
    size_t hex_salt_len){
  /*removing newline character*/
  username[strcspn(username, "\n")] =  '\0';
  password[strcspn(password, "\n")] =  '\0';
  users_directory[strcspn(users_directory, "\n")] = '\0';

  /*check for null pointers*/
if (!users_directory || !username || !password ){
    log_error("null string given , in funtion : login");
    return ERROR_NULL_VALUE_GIVEN;
  }

/*check the langhts of strings given*/
  if(strnlen(password,str_maxlen) >= str_maxlen  ||
    strnlen(username,str_maxlen) >= str_maxlen  ||
    strnlen(path,str_maxlen) >= str_maxlen )

    return ERROR_TOO_LONG_STRING;


  size_t err = 0;
  unsigned char bin_salt[bin_salt_len];
  unsigned char bin_hash[bin_hash_len];
  char hex_salt[hex_salt_len];
  char hex_hash[hex_hash_len];
  char path_userfile[2*str_maxlen];

/*making salt*/
  if (!RAND_bytes(bin_salt, bin_salt_len)) return handleErrors();

  /*making  the path to the file like .../userdirect/username*/
  if ( SUCCESS != (err = make_file_path(
    path_userfile,users_directory,username,str_maxlen)))
    return err;

  /*checking if there's already a user with that username*/
  if(SUCCESS == user_exists(users_directory,
                            username,
                            str_maxlen)){
    log_eror("eror while making new user : user already exists")
    return ERROR_REGISTER_USER_EXISTS;
  }

  if (NULL == fopen(path_userfile,"w")){
    log_eror("eror while making new user : couldnt make userfile")
  }

  /*hashing the password*/
  if (SUCCESS != 
    (err = hash_sha256(password,
                       bin_salt,bin_hash))){
    return err;}

/*converting hash and password to hex*/
  binary_to_hex(bin_salt,SHA256_SALT_SIZE,hex_salt);
  binary_to_hex(bin_hash,SHA256_HASH_SIZE_BYTES,hex_hash);

/*putting them in the user file*/
  if (NULL == fprintf(file, "%s%s", hex_salt, hex_hash)
  ) {

    log_error("user_make: error occurred writing to the file\n");
    fclose(file);
    return ERROR_STDLIB_FUNTION_FAILURE;
  }
  fclose(file);
  return SUCCESS;
}
