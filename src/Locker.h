#include "includes.h"

/*******UNIT TESTS*******/






/*****FUNTIONALITY FUNCTIONS *****/

/*self explanatory i guess*/
int simple_login(char *username,char *password){
  if(!username || !password){
    return errno = ERROR_NULL_VALUE_GIVEN;
  }
  char *Locker_folder = malloc(2*MAXLEN*sizeof(char));
  char *users_folder  = malloc((2*MAXLEN)*sizeof(char));
  if (SUCCESS !=
      define_paths(Locker_folder,
        users_folder,
        NULL,
        NULL,
        MAXLEN,
        pwd))
    return errno;
  login(users_folder,
      username,
      password,
      MAXLEN,
      SHA256_HASH_SIZE_BYTES,
      SHA256_SALT_SIZE,
      SHA256_HASH_SIZE_HEX,
      SHA256_SALT_SIZE_HEX,
      EVP_sha256);

  free(users_folder);
  free(Locker_folder);
  return  errno ;
}
/*look at the initialize_user funtion docs*/
int simple_initialize(void){
  if (SUCCESS !=  initialize_user(
        list_of_config_parameters,
        NUMBER_OF_CONFIGS,
        MAXLEN,
        SHA256_HASH_SIZE_BYTES,
        SHA256_SALT_SIZE,
        SHA256_HASH_SIZE_HEX,
        SHA256_SALT_SIZE_HEX,
        LINE_MAX_LENGHT,
        LINE_MAX_LENGHT,
        NUMBER_OF_DIRS,
        EVP_sha256
        ))
    return errno;
  return (errno = SUCCESS);
}

/*this creates a new account for a user
 * but it needs some explanation */
int new_account(unsigned char *username ,
    unsigned char *key 
    ) 
{

  /*the folder that has the users accounts*/
  char *accounts_folder = malloc(2*MAXLEN*sizeof(char));

  /*this will hold the cipher of the account 
   * after we convert it to hex*/
  unsigned char *hex = 
    malloc(
        HEX_SIZE(
          CIPHER_SIZE(
            ACCOUNT_MAX_SIZE,
            AES_256_BLOCK_SIZE))*sizeof(char));


  /*the string that will hold the json format of the account*/
  const unsigned char *string,*json_stored_acc_str;
  /*the path to the file of the accont of that specific users*/
  char *user_accounts = malloc(3*MAXLEN*sizeof(char));
  FILE *accounts_file;
  /*the cipher obvio*/
  unsigned char cipher_acc[CIPHER_ACCOUNT_MAX_SIZE];
  size_t ciphersize;

  cJSON *json = cJSON_CreateObject();
  if(NULL ==json )
  {
    return errno;
  }
  cJSON* json_stored_acc = cJSON_CreateObject();
  if (NULL == json_stored_acc )
    return errno;
  cJSON *json_item_hexacc = NULL ;
  cJSON *json_item_cipherlen = NULL;
  if(
      NULL == user_accounts ||
      NULL == accounts_folder ||
      NULL == hex)
    return errno = ERROR_MEMORY_ALLOCATION;

  /*defining the path of the folder of users accs 
   * previously declared*/
  if (SUCCESS !=
      define_paths(
        NULL,
        NULL,
        NULL,
        accounts_folder,
        MAXLEN,
        pwd))
    return errno;
  /*defining the path to the exact file that has that user's accs */
  make_file_path(user_accounts,
      accounts_folder,
      (const char * )username,
      MAXLEN);




  if (SUCCESS != errno)
    return errno;
  /*get account from the user*/

  get_data_into_json(json 
      , account_creds_list
      ,ACCOUNTS_INFO
      ,MAXLEN);

  /*make it a jsom object*/
  if (SUCCESS != errno)
    return errno;
  // account_to_json(accc,json);
  if (SUCCESS != errno)
    return errno;
  string = (const unsigned char *)cJSON_Print(json);

  /*encrypting it */
  ciphersize = encrypt_aes256(    
      string,
      strlen((const char *)string),
      key,
      username,
      cipher_acc);
  /*converting to hex for ease of storage*/
  binary_to_hex(
      cipher_acc,
      CIPHER_SIZE(
        strlen((const char *)string),
        AES_256_BLOCK_SIZE),hex);
  /* making the json object that will be stored */
  json_item_hexacc = cJSON_CreateString((const char *)hex);
  json_item_cipherlen = cJSON_CreateNumber(ciphersize);

  cJSON_AddItemToObject(json_stored_acc, "cipher hex",json_item_hexacc);
  cJSON_AddItemToObject(json_stored_acc, "cipher lengh",json_item_cipherlen);
  json_stored_acc_str = (const unsigned char *)cJSON_Print(json_stored_acc  );
  json_item_hexacc = cJSON_DetachItemFromObjectCaseSensitive(json_stored_acc,"cipher hex");

  json_item_cipherlen = cJSON_DetachItemFromObjectCaseSensitive(json_stored_acc,"cipher lengh");

  /*storing it*/

  accounts_file = fopen(user_accounts,"a");
  if(NULL == accounts_file )
  {
    return ERROR_FILE_OPENING_FAILED;
  }
  if (0 > fputs((const char *)json_stored_acc_str,accounts_file ))
  {
    fclose(accounts_file);
    goto free_shit;
    return errno ;
  }
  /*to mark the end of that specific hex*/
  if (0 > fputs("\n",accounts_file ))
  {
    fclose(accounts_file);
    goto free_shit;
    return errno ;
  }

  fclose(accounts_file);

free_shit:
  free(accounts_folder);
  free(hex);
  free(user_accounts);
  if (json) cJSON_Delete(json);
  if (json_stored_acc) cJSON_Delete(json_stored_acc);
  if (json_item_hexacc) cJSON_Delete(json_item_hexacc);  // Free detached item
  if (json_item_cipherlen) cJSON_Delete(json_item_cipherlen);  // Free detached item
  if (string) free((void *)string);
  if (json_stored_acc_str) free((void *)json_stored_acc_str);
  return errno = SUCCESS;
}


int get_account(cJSON *json_acc,
    unsigned char *username,
    unsigned char *key,
    FILE *accounts_file)
{
  unsigned char *string = NULL;
  unsigned char *json_stored_acc_str = NULL;
  /*the cipher obvio*/
  unsigned char cipher_acc[CIPHER_ACCOUNT_MAX_SIZE];
  cJSON *json_cipher_acc = NULL;
  cJSON *json_item_hexacc = NULL;
  cJSON *json_item_cipherlen = NULL;

  // Allocate memory
  string = calloc(ACCOUNT_MAX_SIZE + 99, sizeof(char));
  if (!string) { errno = ENOMEM; goto end; }

  json_stored_acc_str = calloc(MAXLEN * STORED_JSON_LINES, sizeof(char));
  if (!json_stored_acc_str) { errno = ENOMEM; goto end; }

  // Read lines into json_stored_acc_str
  read_lines(json_stored_acc_str, accounts_file, STORED_JSON_LINES, MAXLEN);
  if (errno != SUCCESS) goto end;

  // Parse the JSON
  json_cipher_acc = cJSON_Parse((const char *)json_stored_acc_str);
  if (!json_cipher_acc) {
    fprintf(stderr, "Error before: %s\n", cJSON_GetErrorPtr());
    errno = ERROR_CJSON_LIB_FAILURE;
    goto end;
  }

  // Extract items
  json_item_hexacc = cJSON_GetObjectItemCaseSensitive(json_cipher_acc, "cipher hex");
  json_item_cipherlen = cJSON_GetObjectItemCaseSensitive(json_cipher_acc, "cipher lengh");
  if (!json_item_hexacc || !json_item_cipherlen) {
    errno = ERROR_CJSON_LIB_FAILURE;
    goto end;
  }

  // Convert hex to binary and decrypt
  hex_to_binary(json_item_hexacc->valuestring, cipher_acc, json_item_cipherlen->valuedouble);
  decrypt_aes256(cipher_acc, json_item_cipherlen->valuedouble, key, username, string);
  if (errno != SUCCESS) goto end;

  // Output the decrypted JSON string
  json_acc = cJSON_Parse((const char* ) string);

end:
  if (json_cipher_acc) cJSON_Delete(json_cipher_acc);
  free(string);
  free(json_stored_acc_str);
  return errno;
}

/*self explanatory*/
int display_accounts(unsigned char *username ,
    unsigned char *key )
{
  /*the folder that has the users accounts*/
  char *accounts_folder = malloc(2*MAXLEN*sizeof(char));


  /*the path to the file of the accont of that specific users*/
  char *user_accounts = calloc(3*MAXLEN,sizeof(char));
  FILE *accounts_file;
  cJSON* json_stored_acc = NULL;

  if( 
      NULL == user_accounts ||
      NULL == accounts_folder 
    )
    return errno = ERROR_MEMORY_ALLOCATION;

  /*defining the path of the folder of users accs 
   * previously declared*/
  if (SUCCESS !=
      define_paths(
        NULL,
        NULL,
        NULL,
        accounts_folder,
        MAXLEN,
        pwd))
    return errno;
  /*defining the path to the exact file that has that user's accs */
  make_file_path(user_accounts,
      accounts_folder,
      (const char * )username,
      MAXLEN);

  accounts_file = fopen(user_accounts,"r");
  if(NULL == accounts_file )
  {
    return ERROR_FILE_OPENING_FAILED;
  }
  while( SUCCESS == get_account(json_stored_acc,
        username,
        key,
        accounts_file)
        )//reads one string containing one json object
  {
  cJSON_Delete(json_stored_acc);
  }
  cJSON_Delete(json_stored_acc);
  fclose(accounts_file);
  free(accounts_folder);
  free(user_accounts);

  return errno = SUCCESS;

}

