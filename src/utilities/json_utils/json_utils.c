#include "json_utils.h"
int get_data_into_json(cJSON *json_obj, const char *list[],
                const char *list_clarifications[] ,
                int number_of_inf,
                size_t maxlen)
{


  char **array_credentials =malloc(number_of_inf*sizeof(char*));
  if(!array_credentials)
    return errno = ERROR_MEMORY_ALLOCATION;
  /*initializing the structs in the array */

  if (NULL == json_obj)
  { errno = ERROR_MEMORY_ALLOCATION;
    goto free_resources;
  }

  /*requesting info from the user*/
  getinfo(list,
          list_clarifications,
          number_of_inf,
          maxlen,
          array_credentials);
  if(SUCCESS != errno )
  { 
    goto free_resources;
  }

  for(int i =0;i<number_of_inf;++i){
        if (NULL ==
      cJSON_AddStringToObject(json_obj,
                              list[i], 
                              array_credentials[i]))
  { 
      errno = ERROR_JSON_ADDING_ITEM_TO_OBJ; 
      goto free_resources;
  }
    }
  if(SUCCESS != errno )
    return errno;
free_resources:
  free_array((void **)array_credentials, number_of_inf);
  return errno;
}

/*does the opposite of the decrypt_json function*/
/*this fucntion doesnt need encrypted_json to be allocated*/
/*freeing the encrypted json is on the caller*/
int encrypt_json(
                    cJSON *json,
                    cJSON **encrypted_json,
                    unsigned char *username,
                    unsigned char *key,
                    const EVP_CIPHER * (*EVP_CBC_FUNC)(void)
                    )

{
  /*the string that will hold the json format of the account*/
  cJSON *json_item_hexacc = NULL ;
  cJSON *json_item_cipherlen = NULL;
  int ciphersize;
  unsigned char cipher_acc[CIPHER_ACCOUNT_MAX_SIZE];
const unsigned char *string = NULL;
  /*this will hold the cipher of the account 
   * after we convert it to hex*/
  unsigned char *hex = 
    malloc(
      HEX_SIZE(
        CIPHER_SIZE(
          ACCOUNT_MAX_SIZE,
          AES_256_BLOCK_SIZE))*sizeof(char));
  if(NULL == hex){

    errno=ERROR_MEMORY_ALLOCATION;
    goto free_resources;
  }

  if (NULL ==json || 
    NULL == username || 
    NULL == key || 
    NULL ==EVP_CBC_FUNC)
  {
 errno= ERROR_NULL_VALUE_GIVEN;
    goto free_resources;
  }
  string = (const unsigned char *)cJSON_Print(json);
  if (NULL == string) {
    errno = ERROR_JSON_PRINTING;
    goto free_resources;
  }
  ciphersize = encrypt(    
    string,
    strlen((const char *)string),
    key,
    username,
    cipher_acc,
    EVP_CBC_FUNC);
  
  /*converting to hex for ease of storage*/
  binary_to_hex(
    cipher_acc,
    CIPHER_SIZE(
      strlen((const char *)string),
      AES_256_BLOCK_SIZE),hex);
  /* making the json object that will be stored */
  if (NULL == (json_item_hexacc = 
    cJSON_CreateString((const char *)hex)))
  {
    errno =ERROR_JSON_ADDING_ITEM_TO_OBJ;
    goto free_resources;
  }
  if (NULL == (json_item_cipherlen = 
      cJSON_CreateNumber(ciphersize)))
  {
    errno =ERROR_JSON_ADDING_ITEM_TO_OBJ;
    goto free_resources;
  }
  
  cJSON *temporay = cJSON_CreateObject();
  
  if ( NULL ==temporay )
  {
    errno = ERROR_CJSON_LIB_FAILURE;
    goto free_resources;
  }
  
    cJSON_AddItemToObject(temporay,
                          "cipher hex",
                          json_item_hexacc);
    cJSON_AddItemToObject(temporay,
                          "cipher lengh",
                          json_item_cipherlen);
  *encrypted_json = temporay ;
  errno = SUCCESS;
free_resources:
  free(hex);
  free((void *)string);
  return errno;
}

/*gets a json that has two objects 
 * first a hex of a cipher of the encryptedj son 
 * the second is the lenght of the cipher
 
 it puts the decrypted json in json variable*/
/*freeing the decrypted json is on the caller*/
int decrypt_json(                    
                    cJSON *encrypted_acc_json,
                    cJSON **json,
                    unsigned char *username,
                    unsigned char *key,
                    const EVP_CIPHER * (*EVP_CBC_FUNC)(void)
)
{

  unsigned char cipher_acc[CIPHER_ACCOUNT_MAX_SIZE];
  cJSON *json_item_hexacc = NULL;
  cJSON *json_item_cipherlen = NULL;
  unsigned char* string = NULL ;

  if ( NULL == encrypted_acc_json )
  {
  
    errno = ERROR_NULL_VALUE_GIVEN;
    goto end;
  }
  
  // Allocate memory
  string = calloc(ACCOUNT_MAX_SIZE + 99, sizeof(char));
  if (!string) { errno = ERROR_MEMORY_ALLOCATION; goto end; }

  // Extract items

  if ( NULL == (
    json_item_hexacc = 
    cJSON_GetObjectItemCaseSensitive(encrypted_acc_json,
                                     "cipher hex")
    ) 
  )
  {
    errno =ERROR_JSON_ADDING_ITEM_TO_OBJ;
    goto end;
  }
  if ( NULL == (
  json_item_cipherlen = 
    cJSON_GetObjectItemCaseSensitive(encrypted_acc_json,
                                     "cipher lengh")
    ) 
  )
  {
    errno =ERROR_JSON_ADDING_ITEM_TO_OBJ;
    goto end;
  }
  if (NULL == json_item_hexacc || 
    NULL ==json_item_cipherlen) {
    errno = ERROR_CJSON_LIB_FAILURE;
    goto end;
  }

  // Convert hex to binary and decrypt
  hex_to_binary(json_item_hexacc->valuestring, cipher_acc, json_item_cipherlen->valuedouble);
  decrypt(cipher_acc,
      json_item_cipherlen->valuedouble,
      key,
      username,
      string,
      EVP_CBC_FUNC);
  if (errno != SUCCESS) goto end;

  // Output the decrypted JSON string
*json  = cJSON_Parse((const char* ) string);
  if ( NULL == json )
  {
    errno = ERROR_CJSON_LIB_FAILURE;
    goto end;
  }
  
  if ( NULL == json )
  {
    errno = ERROR_CJSON_LIB_FAILURE;
    goto end;
  }

end:
  free((void *)string);
  return errno;
}
