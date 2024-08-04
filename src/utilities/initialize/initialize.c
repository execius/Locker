// char **initialize(char** listofwantedinfo , int numberofinfos , int maxlengh);
#include "initialize.h"




/*requests the stuff in aarray from the user
 and returns an array of couples (key/value)that
 includes the wanted info label and the user answer*/
int getinfo(const char* listofwantedinfo[] ,
            int numberofinfos , 
            int maxlengh ,
            pair **listofanswers)
{
  //error hamdling
  if (!listofanswers || !listofwantedinfo) {
    log_error(
      "error : NULL given, function : getinfo");
    return ERROR_NULL_VALUE_GIVEN;

  }
  //putting the values in the pair couple
  for (int i = 0 ; i < numberofinfos ;i++){
    listofanswers[i] = malloc(sizeof(pair));
    if(!listofwantedinfo)
        return ERROR_MEMORY_ALLOCATION;
    if(SUCCESS != initialize_pair(listofanswers[i]))
      return errno;
    printf("\n %s > ",listofwantedinfo[i]);
    fgets(listofanswers[i]->value,maxlengh,stdin);

    if(2 > strlen(listofanswers[i]->value))
    {
      log_error("input string too short");
      return ERROR_STR_TOO_SHORT;
    }

    strncpy(listofanswers[i]->key,
            listofwantedinfo[i],
            maxlengh);
    //sanitizing the content
    listofanswers[i]->key[strcspn(listofanswers[i]->key, "\n")] =  '\0';
    listofanswers[i]->value[strcspn(listofanswers[i]->value, "\n")] =  '\0';
  }
  return SUCCESS;
}

int initialize(char *config_folder,
               char *users_folder,
               const char *list_of_wanted_inf[MAXLEN],
               int number_of_inf,
               int maxlengh,
               size_t bin_hash_len,
               size_t bin_salt_len,
               size_t hex_hash_len,
               size_t hex_salt_len,
               size_t line_maxlen,
               size_t path_maxlen
               )
{
  int err = 0;
  if(!config_folder || !list_of_wanted_inf)
    return ERROR_NULL_VALUE_GIVEN;
  char *password = malloc(maxlengh*sizeof(char));
  char *username = malloc(maxlengh*sizeof(char));
  char *config_file = malloc(maxlengh*sizeof(char));
  
  if (!password || !username )
    return ERROR_MEMORY_ALLOCATION;

  printf("username> ");
  fgets(username,MAXLEN,stdin);

  printf("password> ");
  fgets(password,MAXLEN,stdin);
if (SUCCESS != (err =
  make_user(users_folder,
            password,
            username,
            maxlengh,
            bin_hash_len,
            bin_salt_len,
            hex_hash_len,
            hex_salt_len)))
    return err;   


  pair **config_couples =malloc(number_of_inf*sizeof(pair*));
  if(!config_couples)
    return ERROR_MEMORY_ALLOCATION;

  if (SUCCESS != (err =getinfo(list_of_wanted_inf,
          number_of_inf,
          maxlengh,
          config_couples)))
    return err;

  if (SUCCESS != (err = make_file_path(
    config_file,
    config_folder,
    username,
    maxlengh
  )))
    return err;

  if (SUCCESS != (err = write_array_of_pairs(config_file,
                       config_couples,
                       number_of_inf,
                       maxlengh,
                       line_maxlen,
                       path_maxlen)))
    return err;
  for (int i = 0 ; i < number_of_inf ;i++)
    if(!config_couples[i] )
      free_pair(config_couples[i]) ;
  free(username);
  free(password);
  free(config_file);
  free(config_couples);

  return SUCCESS;
  
}

