#include "json_utils.h"

int get_data_into_json(cJSON *json_obj,
                const char *list[],
                const char *list_clarifications[] ,
                int number_of_inf,
                size_t maxlen)
{

  char **array_credentials =malloc(number_of_inf*sizeof(char*));
  if(!array_credentials)
    return errno = ERROR_MEMORY_ALLOCATION;
  /*initializing the structs in the array */

  if (NULL == json_obj){
    return errno = ERROR_JSON_OBJECT_CREATION;
  }
  getinfo(list,
          number_of_inf,
          list_clarifications,
          maxlen,
          array_credentials);
  if(SUCCESS != errno )
    return errno;

  for(int i =0;i<number_of_inf;++i){
        if (NULL ==
      cJSON_AddStringToObject(json_obj,
                              list[i], 
                              array_credentials[i])){
          return errno =  ERROR_JSON_ADDING_ITEM_TO_OBJ;/*checking for errors*/
        }
    }
  free_str_array(array_credentials, number_of_inf);
  if(SUCCESS != errno )
    return errno;
  return SUCCESS;
}

/*gets a json that has two objects 
 * first a hex of a cipher of the encryptedj son 
 * the second is the lenght of the cipher
 
 it puts the decrypted json in json variable*/
cJSON *encrypt_json(
                    cJSON *json,
                    cJSON *encrypted_json,
                    unsigned char *username,
                    unsigned char *key
                    const EVP_CIPHER * (*EVP_CBC_FUNC)(void);
                    )

{


  /*this will hold the cipher of the account 
   * after we convert it to hex*/
  unsigned char *hex = 
    malloc(
      HEX_SIZE(
        CIPHER_SIZE(
          ACCOUNT_MAX_SIZE,
          AES_256_BLOCK_SIZE))*sizeof(char));
  if(!hex)
    return errno=ERROR_MEMORY_ALLOCATION;
char *string = NULL;

  /*the string that will hold the json format of the account*/
  const unsigned char *string;
  cJSON *json_item_hexacc = NULL ;
  cJSON *json_item_cipherlen = NULL;
  int ciphersize;
  string = (const unsigned char *)cJSON_Print(json);
  ciphersize = encrypt(    
    string,
    strlen((const char *)string),
    key,
    username,
    cipher_acc,
    EVP_CBC_FUNC());
  if(SUCCESS != errno)
    return errno;
  /*converting to hex for ease of storage*/
  binary_to_hex(
    cipher_acc,
    CIPHER_SIZE(
      strlen((const char *)string),
      AES_256_BLOCK_SIZE),hex);
  /* making the json object that will be stored */
  json_item_hexacc = cJSON_CreateString((const char *)hex);
  json_item_cipherlen = cJSON_CreateNumber(ciphersize);

  cJSON_AddItemToObject(encrypted_json,
                        "cipher hex",
                        json_item_hexacc);
  cJSON_AddItemToObject(encrypted_json,
                        "cipher lengh",
                        json_item_cipherlen);
free_resources:
  free(hex);
  free(string);
}

/*does the opposite of the encrypt_json function*/
int decrypt_json(                    
                    cJSON *encrypted_acc_json,
                    cJSON *json,
                    unsigned char *username,
                    unsigned char *key
                    const EVP_CIPHER * (*EVP_CBC_FUNC)(void);
)
{

  unsigned char cipher_acc[CIPHER_ACCOUNT_MAX_SIZE];
  cJSON *json_item_hexacc = NULL;
  cJSON *json_item_cipherlen = NULL;

  // Allocate memory
  string = calloc(ACCOUNT_MAX_SIZE + 99, sizeof(char));
  if (!string) { errno = ERROR_MEMORY_ALLOCATION; goto end; }

  // Extract items
  json_item_hexacc = cJSON_GetObjectItemCaseSensitive(encrypted_acc_json, "cipher hex");
  json_item_cipherlen = cJSON_GetObjectItemCaseSensitive(encrypted_acc_json, "cipher lengh");
  if (!json_item_hexacc || !json_item_cipherlen) {
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
      EVP_CBC_FUNC());
  if (errno != SUCCESS) goto end;

  // Output the decrypted JSON string
  json = cJSON_Parse((const char* ) string);

end:
  free(string);
  return errno;
}
