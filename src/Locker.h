#include "includes.h"

/*****FUNTIONALITY FUNCTIONS *****/

/*self explanatory i guess*/
int simple_login(char *username, char *password) {
  if (!username || !password) {
    return errno = ERROR_NULL_VALUE_GIVEN;
  }
  long MAX_PATH_LENGHT = get_system_max_path();
  char *Locker_folder =
      malloc(MAX_PATH_LENGHT * sizeof(char));
  char *users_folder =
      malloc(MAX_PATH_LENGHT * sizeof(char));
  if (SUCCESS !=
      /*makes the strings to the paths
         of the folders */
      define_paths(Locker_folder, users_folder, NULL, NULL,
                   NULL, MAXLEN, pwd))
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
  long MAX_PATH_LENGHT = get_system_max_path();
  if (SUCCESS !=
      initialize_user(
          list_of_config_parameters, NUMBER_OF_CONFIGS,
          MAXLEN, SHA256_HASH_SIZE_BYTES, SHA256_SALT_SIZE,
          SHA256_HASH_SIZE_HEX, SHA256_SALT_SIZE_HEX,
          MAX_PATH_LENGHT, NUMBER_OF_DIRS, EVP_sha256))
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
  unsigned char *encrypted_json_str = calloc(
      MAXLEN * STORED_JSON_LINES + JSON_OVERHEAD_SIZE,
      sizeof(char));

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

int display_account(cJSON *account_json,
                    const char **credentials_names,
                    int number_of_creds) {
  cJSON **items = malloc(number_of_creds * sizeof(cJSON *));
  size_t max_name_length = 0;

  if (NULL == items) {
    errno = ERROR_MEMORY_ALLOCATION;
    goto free_resources;
  }
  for (int i = 0; i < number_of_creds; i++) {
    size_t name_length = strlen(credentials_names[i]);
    if (name_length > max_name_length) {
      max_name_length = name_length;
    }
  }
  for (int i = 0; i < number_of_creds; i++) {
    items[i] = cJSON_GetObjectItemCaseSensitive(
        account_json, credentials_names[i]);
    if (NULL == items[i]) {
      handle_cjson_error();
      goto free_resources;
    }
    printf("\t%-*s : %s\n", (int)max_name_length,
           credentials_names[i], items[i]->valuestring);
  }

free_resources:
  if (items)
    free(items);
  return errno;
}
/*self explanatory*/
int display_accounts(cJSON **json_accounts_array,
                     int numberofaccounts,
                     const char **credentials_names,
                     int number_of_creds,
                     char *searchterm) {

  cJSON **items = malloc(number_of_creds * sizeof(cJSON *));
  int found = 0;
  switch (numberofaccounts) {
  case 0:
    printf("this user have no accounts yet\n");
    break;
  default:
    break;
  }
  if (NULL == searchterm) {
    for (int i = 0; i < numberofaccounts; i++) {
      printf("%d>\n", i);
      display_account(json_accounts_array[i],
                      credentials_names, number_of_creds);
      if (SUCCESS != errno)
        goto end;
    }
  } else {

    for (int i = 0; i < numberofaccounts; i++) {
      for (int j = 0; j < number_of_creds; j++) {
        items[j] = cJSON_GetObjectItemCaseSensitive(
            json_accounts_array[i], credentials_names[j]);
        if (NULL == items[j]) {
          handle_cjson_error();
          goto end;
        }
        if (NULL !=
            stristr(items[j]->valuestring, searchterm))
          found = 1;
      }
      if (1 == found) {
        printf("%d>\n", i);
        display_account(json_accounts_array[i],
                        credentials_names, number_of_creds);
        if (SUCCESS != errno)
          goto end;
        found = 0;
      }
    }
  }
end:
  if (items)
    free(items);
  return errno;
}
int randpass(int length, char *password, size_t maxlength) {
  if (length >= maxlength) {
    errno = ERROR_TOO_LONG_STRING;
    goto end;
  }
  unsigned char c;
  const char charset[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefgh\
ijklmnopqrstuvwxyz0123456789!@#$%^&*";
  size_t charset_size = sizeof(charset) - 1;
  // Exclude NULL terminator
  if (length < 1) {
    errno = ERROR_BAD_ARGUMENT;
    goto end;
  }
  if (NULL == password) {
    errno = ERROR_NULL_VALUE_GIVEN;
    goto end;
  }
  memset(password, 0, length * sizeof(char));
  for (int i = 0; i < length; i++) {
    do {
      if (RAND_priv_bytes(&c, 1) != LIBSSL_SUCCESS) {
        return errno =
                   ERROR_LIBSSL_FAILURE; // OpenSSL error
      }
    } while (c >= (256 - (256 % charset_size)));
    password[i] = charset[c % charset_size];
  }
end:
  return SUCCESS;
}
