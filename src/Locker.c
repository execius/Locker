#include "Locker.h"

int main(int argc, char *argv[]) {
  /*this program works by first scannig the files containing
   * the encrypted accounts place them in an array ,
   * decrypting them and do any reading or modification
   * needed then rewriting them into the file*/

  /*the accs are stored in a json array the json data
   * structure is provided by the Cjson library*/

  int number_of_accounts;
  /* those two are the arrays , the latter is used in the
   * encrypting and writing process while the first is what
   * we read/modify during the runtime*/

  cJSON **json_accounts_array = NULL;
  cJSON **json_accounts_array_temp = NULL;
  /*this will have the configs , encryption options etc*/
  cJSON *configs_json = NULL;

  /*the folder that has the users accounts*/
  char *user_accounts = malloc(3 * MAXLEN * sizeof(char));
  memset(user_accounts, 0, 3 * MAXLEN * sizeof(char));
  /*same with configs folder*/
  char *accounts_folder = malloc(2 * MAXLEN * sizeof(char));
  memset(accounts_folder, 0, 2 * MAXLEN * sizeof(char));
  /*the path to the file of the accont of that specific
   * users*/
  FILE *accounts_file = NULL;
  /*same*/
  FILE *configs_file = NULL;
  /*this is for storing the parsed strings from the jsons*/
  char *json_str = NULL;
  /*same but with the configs jsons instead of the
   * accounts*/
  char *configs_json_str = malloc(
      MAXLEN * NUMBER_OF_CONFIGS * 2 * sizeof(char) + 2);
  /*to silence valgrind*/
  memset(configs_json_str, 0,
         MAXLEN * NUMBER_OF_CONFIGS * 2 * sizeof(char));
  /*the folder that has the configs of each user
   * ie :encryption type*/
  char *configs_folder = NULL;
  configs_folder = malloc(2 * MAXLEN * sizeof(char));
  memset(configs_folder, 0, 2 * MAXLEN * sizeof(char));
  /*the actual file of that specific user's config file*/
  char *user_configs = NULL;
  user_configs = malloc(3 * MAXLEN * sizeof(char));
  memset(user_configs, 0, 3 * MAXLEN * sizeof(char));
  /*the encryption scheme that this user have chosen
   * during the creating of the user*/

  const EVP_CIPHER *(*encryption_scheme)(void) = NULL;
  /*see the usage of those two */
  cJSON *encryption_item = NULL;
  /* this is used to store a choice in the modify acc
   * function*/
  char *modify_choice = NULL;
  char *account_choice = NULL;
  long account_num, num;
  char *endptr;

  /* this handles the commandline arguments*/

  /*keeps track of the commandline options */
  int c;
  /*those will hold the values later for login*/
  char *username, *password;
  username = malloc(MAXLEN * sizeof(char) + 1);
  memset(username, 0, MAXLEN * sizeof(char));
  password = malloc(MAXLEN * sizeof(char) + 1);
  memset(password, 0, MAXLEN * sizeof(char));

  /*this is a key derived from the password*/
  unsigned char *key;
  key = malloc(KEY_SIZE_256 * sizeof(char));
  memset(password, 0, KEY_SIZE_256 * sizeof(char));
  /*flags to check if an option is given*/
  int uflg = 0, Pflg = 0, rflg = 0;
  int mflg = 0, vflg = 0, pflg = 0;
  int iflg = 0, nflg = 0, dflg = 0;

  /*getting commandline options and inceasing flags*/
  while ((c = getopt(argc, argv, ":u:P:ar:mvp:ind")) !=
         -1) {
    switch (c) {
    case 'u':
      uflg++;
      /*if -u get username*/
      strncpy(username, optarg, MAXLEN);
      break;
    case 'P':
      Pflg++;
      /*if -P get password*/
      strncpy(password, optarg, MAXLEN);
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
      fprintf(stderr, "Option -%c requires an operand\n",
              optopt);
      return SUCCESS;
      break;
    case '?':
      fprintf(stderr, "Unrecognized option: '-%c'\n",
              optopt);
      return SUCCESS;
      break;
    }
  }
  /*handling flags */

  switch (vflg) {
  case 0:
    break;
  default:
    printf("version %.2f\n", VERSION);
    goto free_stuff;
    return SUCCESS;
    break;
  }
  /*checking that a username and a password were created
   * before preceeding */
  if ((uflg != 1 || Pflg != 1) && iflg == 0) {
    log_error("provide one username and one password");
    goto free_stuff;
    return SUCCESS;
  }
  /*initializing the program at first use to create
   * necessary folders and such*/
  if (iflg != 0) {
    simple_initialize();
    goto free_stuff;
    return errno;
  }

  /*authentication of the user */

  simple_login(username, password);
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
                 (const unsigned char *)username,
                 SHA256_SALT_SIZE, 1, key, KEY_SIZE_256,
                 EVP_ripemd160);
  if (SUCCESS != errno) {
    goto free_stuff;
    return errno;
  }

  /*defining the path of the folder of users accs
   * previously declared*/
  if (SUCCESS != define_paths(NULL, NULL, configs_folder,
                              accounts_folder, MAXLEN, pwd))
    goto free_stuff;
  /*defining the path to the exact file that has that user's
   * accs */
  make_file_path(user_accounts, accounts_folder,
                 (const char *)username, MAXLEN);

  if (SUCCESS != errno)
    goto free_stuff;

  make_file_path(user_configs, configs_folder,
                 (const char *)username, MAXLEN);

  if (SUCCESS != errno) {
    goto free_stuff;
  }

  /*now opening the accounts file and doing the decryption
   */
  accounts_file = fopen(user_accounts, "r");
  if (NULL == accounts_file) {
    goto free_stuff;
  }

  configs_file = fopen(user_configs, "r");
  if (NULL == configs_file) {
    goto free_stuff;
  }
  /*getting the json that has the configs*/
  /*that +2 is for the brackets of the json*/
  read_lines((unsigned char *)configs_json_str,
             configs_file, NUMBER_OF_CONFIGS + 2, MAXLEN);
  if (errno != SUCCESS)
    goto free_stuff;

  fclose(configs_file);
  // Parse the JSON
  configs_json =
      cJSON_Parse((const char *)configs_json_str);

  if (NULL == configs_json) {
    handle_cjson_error();
    goto free_stuff;
  }

  encryption_item = cJSON_GetObjectItemCaseSensitive(
      configs_json, "encryption");

  if (NULL == encryption_item) {
    handle_cjson_error();
    goto free_stuff;
  }
  if (SUCCESS != errno)
    goto free_stuff;
  /*setting the encryption_scheme after we parsed the
   * configs*/

  switch (atoi(encryption_item->valuestring)) {
  case 1:
    encryption_scheme = EVP_aes_256_cbc;
    break;
  case 2:
    encryption_scheme = EVP_aes_192_cbc;
    break;
  case 3:
    encryption_scheme = EVP_aes_128_cbc;
    break;
  case 4:
    encryption_scheme = EVP_camellia_128_cbc;
    break;
  case 5:
    encryption_scheme = EVP_camellia_192_cbc;
    break;
  case 6:
    encryption_scheme = EVP_camellia_256_cbc;
    break;
  }

  for (number_of_accounts = 0; SUCCESS == errno;
       ++number_of_accounts) {
    if (NULL ==
        (json_accounts_array = realloc(
             json_accounts_array,
             (number_of_accounts + 1) * sizeof(cJSON *)))) {
      errno = ERROR_MEMORY_ALLOCATION;
      goto free_stuff;
    }
    get_next_json_from_file(
        &json_accounts_array[number_of_accounts],
        (unsigned char *)username, key, encryption_scheme,
        accounts_file);

    /* number_of_accounts+1 since we need some memory at
     * first when the number_of_accounts is 0 , then there's
     * always one allocation ahead*/
  }
  errno = SUCCESS;
  number_of_accounts -= 1;
  /*cause it fails once but the number.. still increases
   * by one until the next check the error isnt flaged*/

  printf("accounts fetched there are now %d accs\n",
         number_of_accounts);
  fclose(accounts_file);

  /*handling the creation of a new user*/
  if (nflg != 0) {
    if (NULL == json_accounts_array &&
        NULL == (json_accounts_array =
                     realloc(json_accounts_array,
                             (number_of_accounts + 1) *
                                 sizeof(cJSON *)))) {
      return ERROR_MEMORY_ALLOCATION;
    }

    new_account(json_accounts_array, &number_of_accounts);

    if (SUCCESS != errno) {
      goto free_stuff;
    }
    number_of_accounts += 1;
    printf("new acc have been created m there are now %d "
           "accs\n",
           number_of_accounts);
    json_str = (char *)cJSON_Print(
        json_accounts_array[number_of_accounts - 1]);
    if (NULL == json_str) {
      errno = ERROR_JSON_PRINTING;
      goto free_stuff;
    }
    free(json_str);
  }

  /*displaying the accounts*/
  if (dflg != 0) {
    display_accounts(json_accounts_array,
                     number_of_accounts, account_creds_list,
                     ACCOUNTS_INFO);
  }

  if (mflg != 0) {
    account_choice = malloc(10 * sizeof(char *));
    modify_choice = malloc(10 * sizeof(char *));
    char *newline;
  get_mod_number:
    printf("What do you want to modify :\n");
    for (int i = 0; i < ACCOUNTS_INFO; i++) {
      printf("\t%d)%s\n", i, account_creds_list[i]);
    }
    printf(">");
    fgets(modify_choice, 10, stdin);

    num = strtol(modify_choice, &endptr, 10); // Base 10
    newline = strchr(modify_choice, '\n');
    if (newline) {
      *newline = '\0';
    }
    if (*endptr != '\0' || num >= ACCOUNTS_INFO ||
        num < 0) {
      clear_terminal();
      printf("Invalid input: %s\n", modify_choice);

      if (NULL == modify_choice) {
        errno = ERROR_MEMORY_ALLOCATION;
        goto free_stuff;
      }
      goto get_mod_number;
    }
  get_account_number:
    printf("What account you wanna modify\
    (provide its number) : ");
    fgets(account_choice, 10, stdin);

    char *endptr;
    account_num =
        strtol(account_choice, &endptr, 10); // Base 10

    newline = strchr(account_choice, '\n');
    if (newline) {
      *newline = '\0';
    }
    if (*endptr != '\0' ||
        account_num > number_of_accounts || num < 0) {
      clear_terminal();
      printf("Invalid input: %s\n", account_choice);

      if (NULL == account_choice) {
        errno = ERROR_MEMORY_ALLOCATION;
        goto free_stuff;
      }
      goto get_account_number;
    }

    char *newvalue = malloc(MAXLEN * sizeof(char));
    printf("enter the new value >");
    fgets(newvalue, MAXLEN, stdin);

    modify_json(json_accounts_array[account_num],
                account_creds_list[num], newvalue, MAXLEN);
    if (newvalue)
      free(newvalue);
    if (account_choice)
      free(account_choice);
    if (modify_choice)
      free(modify_choice);
  }

  /* encrypting the accounts,
   * opening the accounts file
   * and then wrinting them to it  */

  if (NULL != json_accounts_array) {
    for (int i = 0; i < number_of_accounts; i++) {
      if (NULL == (json_accounts_array_temp =
                       realloc(json_accounts_array_temp,
                               (i + 1) * sizeof(cJSON *))))
        return ERROR_MEMORY_ALLOCATION;

      encrypt_json(json_accounts_array[i],
                   json_accounts_array_temp + i,
                   (unsigned char *)username, key,
                   encryption_scheme);

      if (SUCCESS != errno) {
        goto free_stuff;
      }
    }
    accounts_file = fopen(user_accounts, "w");
    for (int i = 0; i < number_of_accounts; i++) {
      json_str =
          (char *)cJSON_Print(json_accounts_array_temp[i]);
      if (NULL == json_str) {
        handle_cjson_error();
        goto free_stuff;
      }
      fputs(json_str, accounts_file);
      fputs("\n", accounts_file);
      free(json_str);
    }
    free_cjson_array(json_accounts_array,
                     number_of_accounts);
    free_cjson_array(json_accounts_array_temp,
                     number_of_accounts);
  }
  fclose(accounts_file);
free_stuff:
  if (username)
    free(username);
  if (key)
    free(key);
  if (password)
    free(password);
  if (accounts_folder)
    free(accounts_folder);
  if (user_configs)
    free(user_configs);
  if (user_accounts)
    free(user_accounts);
  if (configs_folder)
    free(configs_folder);
  if (configs_json_str)
    free(configs_json_str);
  printf("%d\n", errno);
  if (configs_json)
    cJSON_Delete(configs_json);
  return errno;
}
