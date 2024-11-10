#include "includes.h"

/*******UNIT TESTS*******/



// int testeditstruct(void){
//   account accc;
//   if(initialize_account(&accc) == SUCCESS ){
//     for(int i = 0 ; i<NUMBEROFINFO;i++){
//       printf("%d>",i);
//       fgets(accc.array[i],MAXLEN,stdin);}
//
//     printf("%s\n %s\n %s\n %s\n %d\n",accc.array[USERINDEX],accc.array[EMAILINDEX],accc.array[PASSWORDINDEX],accc.array[PLATFORMINDEX],*accc.accountnumber);
//     changemember(&accc,0,"99",INT_TYPE);
//     changemember(&accc,USERINDEX,"newname",CHAR_TYPE);
//     printf("%s\n %s\n %s\n %s\n %d\n",accc.array[USERINDEX],accc.array[EMAILINDEX],accc.array[PASSWORDINDEX],accc.array[PLATFORMINDEX],*accc.accountnumber);
//     free_account(&accc);
//     return SUCCESS;
//   }
//   else
//     return -1;
// }
//
// int testprdup(void){
//   account *acc = malloc(sizeof(account));
//   account *ac = malloc(sizeof(account));
//   int error ;
//   if (SUCCESS != ( error = initialize_account(acc))) return error ;
//   if (SUCCESS != ( error = initialize_account(ac))) return error ;
//
//   for(int i = 0 ; i<NUMBEROFINFO;i++){
//     printf("%d>",i);
//     fgets(acc->array[i],MAXLEN,stdin);
//   }
//   *acc->accountnumber = 9;
//   if (SUCCESS != (error = accountdup(acc,ac)) ) return error;
//   free_account(acc);
//   printaccount(ac);
//   free_account(ac);
//   free(acc);
//   free(ac);
//   return SUCCESS;
//
// }
//
// int testparse(void){
//   int eror_tracker = 0;
//   pair **array = malloc(4*sizeof(pair ));
//   FILE *file_pointer = fopen(USER_CONFIG_FILE,"r");
//
//   if(NULL == file_pointer){//checking if the file has been successfully opened
//     log_error("error: could not open file " );
//     return ERROR_FILE_OPENING_FAILED;
//   }
//
//   for(int i = 0 ; i<NUMBER_OF_CONFIG_INFORMATION;i++){
//     array[i] = malloc(sizeof(pair));
//   }
//
//   if (SUCCESS == (eror_tracker = parse_file(file_pointer ,array,LINE_MAX_LENGHT,MAXLEN,NUMBER_OF_CONFIG_INFORMATION)))
//     for(int i = 0 ; i<NUMBER_OF_CONFIG_INFORMATION;i++){
//       printf("key : %s \nvalue : %s \n",array[i]->key,array[i]->value);
//     }
//   for(int i = 0 ; i<NUMBER_OF_CONFIG_INFORMATION;i++){
//     free_pair(array[i]);
//     free(array[i]);
//   }
//   free(array);
//   return SUCCESS;
// }
// int testjson(void){
//   account *accc = malloc(sizeof(account )) ;
//   int error_tracker;
//   cJSON *json = cJSON_CreateObject();
//   if (SUCCESS != (error_tracker = initialize_account(accc))){
//     log_error("could not initialize account , locker.h");
//     return error_tracker;
//   }
//   for(int i = 0 ; i<NUMBEROFINFO;++i){
//     printf("%d>",i);
//     fgets(accc->array[i],MAXLEN,stdin);}
//
//   if (SUCCESS != (error_tracker = account_to_json(accc,json))){
//     log_error("account to json eror");
//     return error_tracker;
//   }
//   char *string = cJSON_Print(json);
//   printf("%s\n",string);
//   free(string);
//
//   account *acc2 = malloc(sizeof(account));
//   if (SUCCESS != (error_tracker = initialize_account(acc2))){
//     log_error("could not initialize account , locker.h");
//     return error_tracker;
//   }
//   json_to_account(json,acc2);
//   printaccount(acc2);
//   free_account(accc);
//   free_account(acc2);
//   free(acc2);
//   free(accc);
//   cJSON_Delete(json);
//   return SUCCESS;
// }
// int testhash(void){
//   int err = 0;
//   const char *pass = "holamia";
//   unsigned char salt[SHA256_SALT_SIZE];
//   unsigned char hash[SHA256_HASH_SIZE_BYTES];
//   if (SUCCESS != (err = hash_sha256(pass,salt,hash)))
//     return err;
//
//   printf("hash is:\n");
//   for (int i = 0; i < SHA256_HASH_SIZE_BYTES; i++) {
//     printf("%02x", hash[i]);
//   }
//   printf("\n");
//
//
//   return SUCCESS;
// }
//
// int testenc(void){
//   int err = 0;
//   const unsigned char* plain = (const unsigned char*)"hoooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooola";
//   unsigned char key [32];
//   unsigned char cipher[MAX_CIPHER_SIZE];
//   unsigned char iv[16];
//   // if (!RAND_bytes(key, sizeof(key))) return handleErrors();
//   if (!RAND_bytes(iv, sizeof(iv))) return handleErrors();
//   hashing_global("lulz",iv,sizeof(iv),3,key,sizeof(key),EVP_sha256);
//   if (SUCCESS != (err = encrypt_aes256(plain,MAXLEN,key,iv,cipher)) )
//     return err;
//   printf("Ciphertext is:\n");
//   for (int i = 0; i < MAX_CIPHER_SIZE; i++) {
//     printf("%02x", cipher[i]);
//   }
//   printf("\n");
//   unsigned char plaintxt[MAXLEN];
//   char password[32];
//   unsigned char key2[32];
//   fgets(password,32,stdin);
//   password[strcspn(password, "\n")] =  '\0';
//   hashing_global(password,iv,sizeof(iv),3,key2,sizeof(key),EVP_sha256); 
//   decrypt_aes256(cipher, MAX_CIPHER_SIZE, key2,iv, plaintxt);
//   printf("\n\n\n\nplaintext : %s\n",plaintxt);
//
//   return SUCCESS;
//
// }

// int testconfwriter(void){
//   pair *array[NUMBER_OF_CONFIGS] ;
//   for(int i = 0 ; i<NUMBER_OF_CONFIGS;i++){
//     array[i] = malloc(sizeof(pair));
//     initialize_pair(array[i]);
//   }
//
//
//   for(int i = 0 ; i<NUMBER_OF_CONFIGS;i++){
//     printf("key>");
//     fgets(array[i]->key,MAXLEN,stdin);
//     printf("value>");
//     fgets(array[i]->value,MAXLEN,stdin);
//   }
//
//   if (SUCCESS != write_array_of_pairs(
//         "config.txt",
//         array,
//         NUMBER_OF_CONFIGS,
//         MAXLEN,
//         LINE_MAX_LENGHT,
//         LINE_MAX_LENGHT)){
//     for(int i = 0 ; i<NUMBER_OF_CONFIGS;i++){
//       free_pair(array[i]);
//       free(array[i]);
//     }
//     return errno;
//   }
//   for(int i = 0 ; i<NUMBER_OF_CONFIGS;i++){
//     free_pair(array[i]);
//     free(array[i]);
//   }
//
//
//   return errno;
//
//   return SUCCESS;
//
// }
//
//








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
        list_of_wanted_inf,
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

  get_account(json 
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


/*self explanatory*/
int display_accounts(unsigned char *username ,
    unsigned char *key )
{
  /*the folder that has the users accounts*/
  char *accounts_folder = malloc(2*MAXLEN*sizeof(char));

  /*this will hold the cipher of the account 
   * after we convert it to hex*/

  /*the string that will hold the json format of the account*/
  unsigned char*string = NULL;
    string= calloc(ACCOUNT_MAX_SIZE+99,sizeof(char)); /*+100 for json syntax*/

  unsigned char *json_stored_acc_str = NULL;
    json_stored_acc_str= calloc(MAXLEN*STORED_JSON_LINES,sizeof(char));
  /*the path to the file of the accont of that specific users*/
  char *user_accounts = calloc(3*MAXLEN,sizeof(char));
  FILE *accounts_file;
  /*the cipher obvio*/
  unsigned char cipher_acc[CIPHER_ACCOUNT_MAX_SIZE];
  // cJSON *json = cJSON_CreateObject();
  // if(NULL ==json )
  // {
  //   return errno;
  // }
cJSON* json_stored_acc ;
cJSON *json_item_hexacc = NULL ;
cJSON *json_item_cipherlen = NULL;
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
  /*this is the main sequence , in which unpacking and decryption happens */
  int check;
while( SUCCESS == //reads one string containing one json object
  ( check = read_lines(json_stored_acc_str,
      accounts_file,
      STORED_JSON_LINES,//how many lines a json object is 
      MAXLEN)) )
{


  /*parsing the string*/
  json_stored_acc = 
    cJSON_Parse((const char *)json_stored_acc_str);
  if (json_stored_acc == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return errno = ERROR_CJSON_LIB_FAILURE;
    }

  /*extracting the cipher hex and the lengh of it from the json*/
 json_item_hexacc = 
   cJSON_GetObjectItemCaseSensitive(
       json_stored_acc,
       "cipher hex"
       );
 json_item_cipherlen = 
   cJSON_GetObjectItemCaseSensitive(
       json_stored_acc,
       "cipher lengh"
       );

 /*converting the hex to the original cipher*/
 hex_to_binary(json_item_hexacc->valuestring,
     cipher_acc,
     json_item_cipherlen->valuedouble);

 /*decrypting the cipher*/
decrypt_aes256(
    cipher_acc,
    json_item_cipherlen->valuedouble,
    key,
    username,
    string);
 if (errno != SUCCESS)
    return errno;
 /*now we got the json containing the account info*/
printf("%s\n",string);
/*renewing the vars used in this loop*/
cJSON_Delete(json_stored_acc);
free(json_stored_acc_str);
free(string);
json_stored_acc_str = calloc(MAXLEN*STORED_JSON_LINES,sizeof(char));
string= calloc(ACCOUNT_MAX_SIZE+JSON_OVERHEAD_SIZE,sizeof(char)); /*+100 for json syntax*/

}
fclose(accounts_file);
free_shit:
  free(accounts_folder);
  free(user_accounts);
  if (string) free((void *)string);
  if (json_stored_acc_str) free((void *)json_stored_acc_str);

return errno = SUCCESS;

}
    
