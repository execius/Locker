#include "includes.h"

/*****FUNTIONALITY FUNCTIONS *****/

/*self explanatory i guess*/
int simple_login(char *username, char *password) {
  if (!username || !password) {
    return errno = ERROR_NULL_VALUE_GIVEN;
  }
  char *Locker_folder = malloc(2 * MAXLEN * sizeof(char));
  char *users_folder = malloc((2 * MAXLEN) * sizeof(char));
  if (SUCCESS !=
      /*makes the strings to the paths
         of the folders */
      define_paths(Locker_folder, users_folder, NULL, NULL,
                   MAXLEN, pwd))
    goto free_resources;
  login(users_folder, username, password, MAXLEN,
        SHA256_HASH_SIZE_BYTES, SHA256_SALT_SIZE,
        SHA256_HASH_SIZE_HEX, SHA256_SALT_SIZE_HEX,
        EVP_sha256);

free_resources:
  free(users_folder);
  free(Locker_folder);
  return errno;
}
/*look at the initialize_user funtion
 * docs*/
int simple_initialize(void) {
  if (SUCCESS !=
      initialize_user(
          list_of_config_parameters, NUMBER_OF_CONFIGS,
          MAXLEN, SHA256_HASH_SIZE_BYTES, SHA256_SALT_SIZE,
          SHA256_HASH_SIZE_HEX, SHA256_SALT_SIZE_HEX,
          LINE_MAX_LENGHT, LINE_MAX_LENGHT, NUMBER_OF_DIRS,
          EVP_sha256))
    return errno;
  return (errno = SUCCESS);
}

/*this creates a new account for a user
 * but it needs some explanation */
int new_account(cJSON **cjson_accounts_array,
                int *number_of_accounts) {
  if (!cjson_accounts_array || !number_of_accounts) {
    errno = ERROR_NULL_VALUE_GIVEN;
    goto end;
  }
  /*allocate memory for json*/
  cjson_accounts_array[*number_of_accounts] =
      cJSON_CreateObject();

  if (NULL == cjson_accounts_array[*number_of_accounts]) {
    handle_cjson_error();
    goto end;
  }
  /*get account informations  from the
   * user into the json*/
  get_data_into_json(
      cjson_accounts_array[*number_of_accounts],
      account_creds_list, list_of_accounts_clarifications,
      ACCOUNTS_INFO, MAXLEN);

  if (SUCCESS != errno) {
    cJSON_Delete(cjson_accounts_array[*number_of_accounts]);
    goto end;
  }
end:
  return errno;
}

int get_next_json_from_file(
    cJSON **json_acc, unsigned char *username,
    unsigned char *key,
    const EVP_CIPHER *(*EVP_CBC_FUNC)(void),
    FILE *accounts_file) {
  /*the string containing the json
   * before we parse it */
  unsigned char *encrypted_json_str =
      calloc(MAXLEN * STORED_JSON_LINES, sizeof(char));

  /*allocate memory fot the json read
   * from the file it's stored encrypted
   * tho*/
  cJSON *json_encrypted = NULL;

  /*errors check*/
  if (!encrypted_json_str) {
    errno = ERROR_MEMORY_ALLOCATION;
    goto end;
  }

  // Read lines into json_stored_acc_str
  // STORED_JSON_LINES is the standard
  // number of lines that a stored json
  // consists of , it's 4 rn
  read_lines(encrypted_json_str, accounts_file,
             STORED_JSON_LINES, MAXLEN);
  if (errno != SUCCESS)
    goto end;
  // Parse the JSON
  json_encrypted =
      cJSON_Parse((const char *)encrypted_json_str);

  if (NULL == json_encrypted) {
    handle_cjson_error();
    goto end;
  }

  decrypt_json(json_encrypted, json_acc, username, key,
               EVP_CBC_FUNC);

  cJSON_Delete(json_encrypted);
end:
  free(encrypted_json_str);
  return errno;
}

/*self explanatory*/
int display_accounts(cJSON **json_accounts_array,
                     int numberofaccounts) {

  switch (numberofaccounts) {
  case 0:
    printf("this user have no accounts "
           "yet\n");
    break;
  default:
    break;
  }
  char *json_str = NULL;
  for (int i = 0; i < numberofaccounts; i++) {
    json_str = (char *)cJSON_Print(json_accounts_array[i]);
    if (NULL == json_str) {
      handle_cjson_error();
      goto end;
    }
    printf("%d\t:%s\n", i, json_str);
    free(json_str);
  }
end:
  return errno = SUCCESS;
}
