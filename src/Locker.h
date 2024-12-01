#include "includes.h"


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
    goto free_resources;
  login(users_folder,
      username,
      password,
      MAXLEN,
      SHA256_HASH_SIZE_BYTES,
      SHA256_SALT_SIZE,
      SHA256_HASH_SIZE_HEX,
      SHA256_SALT_SIZE_HEX,
      EVP_sha256);

free_resources:
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
int new_account(
    cJSON **cjson_accounts_array,
    int number_of_accounts
    ) 
{


  cJSON *json = cJSON_CreateObject();
  if(NULL ==json )
  {
    return errno;
  }
  cJSON* json_stored_acc = cJSON_CreateObject();
  if (NULL == json_stored_acc )
  {
    cJSON_Delete(json);
    return errno;
  }
  /*get account from the user*/
  get_data_into_json(json 
      , account_creds_list
      ,list_of_accounts_clarifications
      ,ACCOUNTS_INFO
      ,MAXLEN);

  if (SUCCESS != errno)
  {
    cJSON_Delete(json);
    return errno;
  }
    /*puting it in the array*/
  cjson_accounts_array[number_of_accounts+1]=json;
  
  return errno = SUCCESS;
}



int get_next_json_from_file(cJSON *json_acc,
    unsigned char *username,
    unsigned char *key,
    const EVP_CIPHER * (*EVP_CBC_FUNC)(void) ,
    FILE *accounts_file
    )
{
  cJSON *json_encrypted = NULL;
  unsigned char *encrypted_json_str = NULL;
  /*the cipher obvio*/


  encrypted_json_str = calloc(MAXLEN * STORED_JSON_LINES, sizeof(char));
  if (!encrypted_json_str) { errno = ENOMEM; goto end; }

  // Read lines into json_stored_acc_str
  read_lines(encrypted_json_str, accounts_file, STORED_JSON_LINES, MAXLEN);
  if (errno != SUCCESS) goto end;

  // Parse the JSON
  json_encrypted = cJSON_Parse((const char *)encrypted_json_str);
  if (!json_encrypted) {
    fprintf(stderr, "Error before: %s\n", cJSON_GetErrorPtr());
    errno = ERROR_CJSON_LIB_FAILURE;
    goto end;
  }
 
  decrypt_json(
      json_encrypted,
      json_acc,
      username,
      key,
      EVP_CBC_FUNC);

  if (errno != SUCCESS) goto end;
end:
  if (json_encrypted) cJSON_Delete(json_encrypted);
  free(encrypted_json_str);
  return errno;
}

/*self explanatory*/
int display_accounts(
    cJSON** json_accounts_array,
    int numberofaccounts)
{
char*  json_str = NULL;
for(int i = 0;i<=numberofaccounts;i++)
{
  
  json_str = (char *)cJSON_Print(json_accounts_array[i]);
  printf("%s\n",json_str);
  if(!json_str)
    free(json_str);
}
return errno=SUCCESS;
}

