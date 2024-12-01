#include "Locker.h"

int main(int argc, char *argv[])
{ 
  /*
   * this handles the commandline arguments*/

/*now opening the accounts file and doing the decryption */
/*the accs are stored in a json array the json data structure 
 * is provided by the Cjson library*/
  cJSON **json_accounts_array = NULL;
  cJSON *configs_json= NULL;

  FILE *accounts_file = NULL;
  FILE *configs_file = NULL;
  /*the folder that has the users accounts*/
  char *accounts_folder =NULL;
  accounts_folder = malloc(2*MAXLEN*sizeof(char));
  /*the path to the file of the accont of that specific users*/
  char *user_accounts = NULL;
  user_accounts = malloc(3*MAXLEN*sizeof(char));
  /*the folder that has the configs of each user 
   * ie :encryption type*/
  char *configs_folder = NULL;
  configs_folder = malloc(2*MAXLEN*sizeof(char));
  /*the actual file of that specific user's config file*/
  char *user_configs = NULL;
  user_configs = malloc(3*MAXLEN*sizeof(char));
  /*the encryption scheme that this user have chosen
   * during the creating of the user*/

 const EVP_CIPHER *(*encryption_sheme)(void) = EVP_aes_256_cbc;
  cJSON *encryption_item= NULL;
  cJSON *hashing_item   = NULL;





  /*keeps track of the commandline options */
  int c;
  /*those will hold the values later for login*/
  char *username,*password;
  username = malloc(MAXLEN*sizeof(char)+1);
  password = malloc(MAXLEN*sizeof(char)+1);

  /*this is a key derived from the password*/
  unsigned char *key ;
  key = malloc(KEY_SIZE_256*sizeof(char));
  /*flags to check if an option is given*/
  int uflg = 0, Pflg = 0, rflg = 0;
  int mflg = 0, vflg = 0,  pflg = 0;
  int iflg = 0, nflg = 0,dflg = 0;

  /*getting commandline options and inceasing flags*/
  while ((c = getopt(argc, argv, ":u:P:ar:m:vp:ind")) != -1) {
    switch(c) {    
      case 'u':
        uflg++;
        /*if -u get username*/
        strncpy(username,optarg,MAXLEN);
        break;
      case 'P':
        Pflg++;
        /*if -P get password*/
        strncpy(password,optarg,MAXLEN);
        break;
      case 'p':
        pflg++;
        break;
      case 'm':
        mflg++;
        break;
      case 'n':
        nflg++;
        break;
      case 'r':
        rflg++;
        break;
      case 'v':
        vflg++;
        break;
      case 'i':
        iflg++;
        break;
      case 'd':
        dflg++;
        break;
      /*misuse handling*/
      case ':':       
        fprintf(stderr,
                "Option -%c requires an operand\n", optopt);
        return SUCCESS;
        break;
      case '?':
        fprintf(stderr,
                "Unrecognized option: '-%c'\n", optopt);
        return SUCCESS;
        break;
    }
  }
  /*handling flags */


  switch (vflg) {
    case 0:
      break;
    default:
      printf("version %.2f\n",VERSION);
      goto free_stuff;
      return SUCCESS;
      break;

  }
  /*checking that a username and a password were created before preceeding */
  if ((uflg!=1 || Pflg != 1) && iflg == 0){
    log_error("provide one username and one password");
    goto free_stuff;
    return SUCCESS;
  }
  /*initializing the program at first use to create necessary folders and such*/
  if (iflg  != 0){
    simple_initialize();
    goto free_stuff;
    return errno;
  }

/*authentication of the user */

  simple_login(username,password);
  switch (errno) {
    case SUCCESS:
      printf("login success\n");
      break;
    default:
      goto free_stuff;
      return errno;
      break;
  }
  /*creating the encryption key from the user password*/

  hashing_global((const char *)password,
             (const unsigned char*)username,
             SHA256_SALT_SIZE,
             1,
             key,
             KEY_SIZE_256,
             EVP_ripemd160);
  if (SUCCESS != errno){
    goto free_stuff;
    return errno;
  }

  /*defining the path of the folder of users accs 
   * previously declared*/
  if (SUCCESS !=
      define_paths(
        NULL,
        NULL,
        configs_folder,
        accounts_folder,
        MAXLEN,
        pwd))
    goto free_stuff;
  /*defining the path to the exact file that has that user's accs */
  make_file_path(user_accounts,
      accounts_folder,
      (const char * )username,
      MAXLEN);

  if (SUCCESS != errno)
    goto free_stuff;
  make_file_path(user_configs,
      configs_folder  ,
      (const char * )username,
      MAXLEN);


  if (SUCCESS != errno){
    goto free_stuff;
  }
  accounts_file = fopen(user_accounts,"r+");
  if(NULL == accounts_file )
  {
    goto free_stuff;
  }
  
  configs_file = fopen(user_configs,"r");
  if(NULL == configs_file )
  {
    goto free_stuff;
  }
  /*getting the json that has the configs*/
  get_next_json_from_file(configs_json,
                          (unsigned char*)username,
                          key,
                          encryption_sheme,
                          configs_file);

  encryption_item = cJSON_GetObjectItemCaseSensitive(configs_json, "encryption");
  hashing_item = cJSON_GetObjectItemCaseSensitive(configs_json, "hashing");
  // switch (encryption_item->valuestring) {
  //   case "1":
  //     break;
  //   case "2":
  //     break;
  //   case "3":
  //     break;
  //   case "4":
  //     break;
  // }
  // switch (encryption_item->valuestring) {
  //   case "1":
  //     break;
  //   case "2":
  //     break;
  //   case "3":
  //     break;
  //   case "4":
  //     break;
  // }
  if (SUCCESS != errno){
    goto free_stuff;
  }

  int number_of_accounts = 0;
  json_accounts_array = malloc(sizeof(cJSON*));
  if(!json_accounts_array )
    return errno = ERROR_MEMORY_ALLOCATION;
  while( SUCCESS == 
    get_next_json_from_file(
      json_accounts_array[number_of_accounts],
      (unsigned char*)username,
      key,
      encryption_sheme,
      accounts_file))
  {
    /* number_of_accounts+1 since we need some memory at first
     * when the number_of_accounts is 0 , then there's always 
     * one allocation ahead*/

    number_of_accounts += 1;
    if(NULL == 
    realloc(json_accounts_array,(number_of_accounts+1)*sizeof(cJSON*))
    )
    {
      return ERROR_MEMORY_ALLOCATION;
    }
  }
  number_of_accounts -= 1;
  
  

  /*handling the creation of a new user*/
  if (nflg  != 0){
    new_account(
                json_accounts_array,
                number_of_accounts) ;
    number_of_accounts += 1;
  }
  /*displaying the accounts*/
  if (dflg  != 0){
    display_accounts(
                json_accounts_array,
                number_of_accounts) ;
  }
  fclose(accounts_file);

free_stuff :
  free(username);
  free(key);
  free(password);
  free(accounts_folder);
  free(user_accounts);
  printf("%d\n",errno);
  if (configs_json) cJSON_Delete(configs_json);
  if (encryption_item) cJSON_Delete(encryption_item);  // Free detached item
  if (hashing_item) cJSON_Delete(hashing_item);  // Free detached item
  return errno;
}
