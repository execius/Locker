#include "login.h"

/*fetches a salt and a hashed password from a user file*/
static int get_salt_nd_hashedpass(const char *users_path,
                                  const char *username,
                                  char *hex_hashed_password,
                                  char *hex_salt,
                                  size_t str_maxlen,
                                  size_t hex_hash_maxlen,
                                  size_t hex_salt_maxlen) {
  /*to track errors*/
  /*user file*/
  FILE *file;
  char pathtofile[2 * str_maxlen];
  /*making  the path to the file like
   * .../userdirect/username*/
  if (SUCCESS != make_file_path(pathtofile, users_path,
                                username, str_maxlen))
    return errno;

  /*check that the user(and therefore the file) exists*/
  if (SUCCESS !=
      user_exists(users_path, username, str_maxlen)) {

    return errno;
  }
  /*open file and check for errors*/
  if (NULL == (file = fopen(pathtofile, "r"))) {
    log_error("eror while retrieving hashed \
password from file ,file exists but cannot be read\n");
    errno = ERROR_CANNOT_READ_FILE;
    return errno;
  }

  if (NULL == fgets(hex_salt, hex_salt_maxlen, file) ||
      NULL == fgets(hex_hashed_password, hex_hash_maxlen,
                    file)) {

    log_error("An error occurred reading the file\n");
    fclose(file);
    errno = ERROR_STDLIB_FUNTION_FAILURE;
    return errno;
  }
  fclose(file);
  return errno = SUCCESS;
}

int login(char *users_path, char *input_username,
          char *input_password, size_t str_maxlen,
          size_t hash_maxlen, size_t salt_maxlen,
          size_t hex_hash_maxlen, size_t hex_salt_maxlen,
          const EVP_MD *(*hash_function)(void)) {
  /*removing newline character*/
  input_username[strcspn(input_username, "\n")] = '\0';
  input_password[strcspn(input_password, "\n")] = '\0';
  users_path[strcspn(users_path, "\n")] = '\0';

  unsigned char input_password_hash[hash_maxlen];
  unsigned char user_password_hash[hash_maxlen];
  unsigned char salt[salt_maxlen];
  char hex_salt[hex_salt_maxlen];
  char hex_hash[hex_hash_maxlen];

  /*check for null pointers*/
  if (!users_path || !input_username || !input_password) {
    log_error("null string given , in funtion : login");
    errno = ERROR_NULL_VALUE_GIVEN;
    return errno;
  }

  /*check the langhts of strings given*/
  if (strnlen(input_password, str_maxlen) >= str_maxlen ||
      strnlen(input_username, str_maxlen) >= str_maxlen ||
      strnlen(users_path, str_maxlen) >= str_maxlen)
    return errno = ERROR_TOO_LONG_STRING;
  /*check that theres a file with the same name as the user
   * this validates if the user is existent*/
  if (SUCCESS !=
      user_exists(users_path, input_username, str_maxlen)) {
    log_error("no such user exists");
    return errno;
  }

  /*getting the hash and salt from the user file*/
  if (SUCCESS != get_salt_nd_hashedpass(
                     users_path, input_username, hex_hash,
                     hex_salt, str_maxlen, hex_hash_maxlen,
                     hex_salt_maxlen)) {
    log_error("could not get salt and \
hashed user password");
    return errno;
  }
  /* Remove newline characters*/
  hex_salt[strcspn(hex_salt, "\n")] = '\0';
  hex_hash[strcspn(hex_hash, "\n")] = '\0';

  /*converting hex hash and salt to binary for comparison*/
  hex_to_binary(hex_salt, salt, salt_maxlen);
  hex_to_binary(hex_hash, user_password_hash, hash_maxlen);

  /*hashing the inserted password to compare it to the user
   * password hash*/
  if (SUCCESS !=
      hashing_global(input_password, salt, salt_maxlen, 1,
                     input_password_hash, hash_maxlen,
                     hash_function)) {
    return errno;
  }
  /*comparison*/
  if (SUCCESS !=
      compare_creds((const char *)input_password_hash,
                    (const char *)user_password_hash,
                    hash_maxlen)) {
    log_error("login error,incorrect password");
    return errno;
  }
  return errno = SUCCESS;
}
