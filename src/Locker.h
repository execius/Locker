#include "includes.h"

int testeditstruct(void){
  account accc;
  if(initialize_account(&accc) == SUCCESS ){
    for(int i = 0 ; i<NUMBEROFINFO;i++){
      printf("%d>",i);
      fgets(accc.array[i],MAXLEN,stdin);}

    printf("%s\n %s\n %s\n %s\n %d\n",accc.array[USERINDEX],accc.array[EMAILINDEX],accc.array[PASSWORDINDEX],accc.array[PLATFORMINDEX],*accc.accountnumber);
    changemember(&accc,0,"99",INT_TYPE);
    changemember(&accc,USERINDEX,"newname",CHAR_TYPE);
    printf("%s\n %s\n %s\n %s\n %d\n",accc.array[USERINDEX],accc.array[EMAILINDEX],accc.array[PASSWORDINDEX],accc.array[PLATFORMINDEX],*accc.accountnumber);
    free_account(&accc);
    return SUCCESS;
  }
  else
    return -1;
}

int testprdup(void){
  account *acc = malloc(sizeof(account));
  account *ac = malloc(sizeof(account));
  int error ;
  if (SUCCESS != ( error = initialize_account(acc))) return error ;
  if (SUCCESS != ( error = initialize_account(ac))) return error ;

  for(int i = 0 ; i<NUMBEROFINFO;i++){
    printf("%d>",i);
    fgets(acc->array[i],MAXLEN,stdin);
  }
  *acc->accountnumber = 9;
  if (SUCCESS != (error = accountdup(acc,ac)) ) return error;
  free_account(acc);
  printaccount(ac);
  free_account(ac);
  free(acc);
  free(ac);
  return SUCCESS;

}

int testparse(void){
  int eror_tracker = 0;
  pair **array = malloc(4*sizeof(pair ));
  FILE *file_pointer = fopen(USER_CONFIG_FILE,"r");

  if(NULL == file_pointer){//checking if the file has been successfully opened
    log_error("error: could not open file " );
    return ERROR_FILE_OPENING_FAILED;
  }

  for(int i = 0 ; i<NUMBER_OF_CONFIG_INFORMATION;i++){
    array[i] = malloc(sizeof(pair));
  }

  if (SUCCESS == (eror_tracker = parse_file(file_pointer ,array,LINE_MAX_LENGHT,MAXLEN,NUMBER_OF_CONFIG_INFORMATION)))
    for(int i = 0 ; i<NUMBER_OF_CONFIG_INFORMATION;i++){
      printf("key : %s \nvalue : %s \n",array[i]->key,array[i]->value);
    }
  for(int i = 0 ; i<NUMBER_OF_CONFIG_INFORMATION;i++){
    free_pair(array[i]);
    free(array[i]);
  }
  free(array);
  return SUCCESS;
}
int testjson(void){
  account *accc = malloc(sizeof(account )) ;
  int error_tracker;
  cJSON *json = cJSON_CreateObject();
  if (SUCCESS != (error_tracker = initialize_account(accc))){
    log_error("could not initialize account , locker.h");
    return error_tracker;
  }
  for(int i = 0 ; i<NUMBEROFINFO;++i){
    printf("%d>",i);
    fgets(accc->array[i],MAXLEN,stdin);}

  if (SUCCESS != (error_tracker = account_to_json(accc,json))){
    log_error("account to json eror");
    return error_tracker;
  }
  char *string = cJSON_Print(json);
  printf("%s\n",string);
  free(string);

  account *acc2 = malloc(sizeof(account));
  if (SUCCESS != (error_tracker = initialize_account(acc2))){
    log_error("could not initialize account , locker.h");
    return error_tracker;
  }
  json_to_account(json,acc2);
  printaccount(acc2);
  free_account(accc);
  free_account(acc2);
  free(acc2);
  free(accc);
  cJSON_Delete(json);
  return SUCCESS;
}
int testhash(void){
  int err = 0;
  const char *pass = "holamia";
  unsigned char salt[SHA256_SALT_SIZE];
  unsigned char hash[SHA256_HASH_SIZE_BYTES];
  if (SUCCESS != (err = hash_sha256(pass,salt,hash)))
    return err;

  printf("hash is:\n");
  for (int i = 0; i < SHA256_HASH_SIZE_BYTES; i++) {
    printf("%02x", hash[i]);
  }
  printf("\n");


  return SUCCESS;
}

int testenc(void){
  int err = 0;
  const unsigned char* plain = (const unsigned char*)"hoooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooola";
  unsigned char key [32];
  unsigned char cipher[MAX_CIPHER_SIZE];
  unsigned char iv[16];
  // if (!RAND_bytes(key, sizeof(key))) return handleErrors();
  if (!RAND_bytes(iv, sizeof(iv))) return handleErrors();
  hashing_global("lulz",iv,sizeof(iv),3,key,sizeof(key),EVP_sha256);
  if (SUCCESS != (err = encrypt_aes256(plain,MAXLEN,key,iv,cipher)) )
    return err;
  printf("Ciphertext is:\n");
  for (int i = 0; i < MAX_CIPHER_SIZE; i++) {
    printf("%02x", cipher[i]);
  }
  printf("\n");
  unsigned char plaintxt[MAXLEN];
  char password[32];
  unsigned char key2[32];
  fgets(password,32,stdin);
  password[strcspn(password, "\n")] =  '\0';
  hashing_global(password,iv,sizeof(iv),3,key2,sizeof(key),EVP_sha256); 
  decrypt_aes256(cipher, MAX_CIPHER_SIZE, key2,iv, plaintxt);
  printf("\n\n\n\nplaintext : %s\n",plaintxt);

  return SUCCESS;

}

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
      SHA256_SALT_SIZE_HEX);

  free(users_folder);
  free(Locker_folder);
  return  errno ;
}

int testconfwriter(void){
  pair *array[NUMBER_OF_CONFIGS] ;
  for(int i = 0 ; i<NUMBER_OF_CONFIGS;i++){
    array[i] = malloc(sizeof(pair));
    initialize_pair(array[i]);
  }


  for(int i = 0 ; i<NUMBER_OF_CONFIGS;i++){
    printf("key>");
    fgets(array[i]->key,MAXLEN,stdin);
    printf("value>");
    fgets(array[i]->value,MAXLEN,stdin);
  }

  if (SUCCESS != write_array_of_pairs(
        "config.txt",
        array,
        NUMBER_OF_CONFIGS,
        MAXLEN,
        LINE_MAX_LENGHT,
        LINE_MAX_LENGHT)){
    for(int i = 0 ; i<NUMBER_OF_CONFIGS;i++){
      free_pair(array[i]);
      free(array[i]);
    }
    return errno;
  }
  for(int i = 0 ; i<NUMBER_OF_CONFIGS;i++){
    free_pair(array[i]);
    free(array[i]);
  }


  return errno;

  return SUCCESS;

}
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
int new_account(unsigned char *username ,
    unsigned char *key 
    ) 
{
  char *accounts_folder = malloc(2*MAXLEN*sizeof(char));
  if (SUCCESS !=
      define_paths(
        NULL,
        NULL,
        NULL,
        accounts_folder,
        MAXLEN,
        pwd))
    return errno;

  unsigned char cipher_acc[CIPHER_ACCOUNT_MAX_SIZE];
  account *accc = malloc(sizeof(account));
  if(NULL == accc)
    return errno = ERROR_MEMORY_ALLOCATION;

  initialize_account(accc);

  if (SUCCESS != errno)
    return errno;

  get_account(accc 
      , account_creds_list
      ,ACCOUNTS_INFO
      ,MAXLEN);

  if (SUCCESS != errno)
    return errno;
  cJSON *json = cJSON_CreateObject();
  account_to_json(accc,json);
  if (SUCCESS != errno)
    return errno;
  const unsigned char *string = 
    (const unsigned char *)cJSON_Print(json);

  printf("%s\n",string);

  encrypt_aes256(    
      string,
      ACCOUNT_MAX_SIZE,
      key,
      username,
      cipher_acc);
  printf("%s\n",cipher_acc);

  if (SUCCESS != errno)
    return errno;
  return errno = SUCCESS;
}
