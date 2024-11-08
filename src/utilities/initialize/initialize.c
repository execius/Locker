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
    printf("\n %s > ",listofwantedinfo[i]);
    fgets(listofanswers[i]->value,maxlengh,stdin);

    if(2 > strlen(listofanswers[i]->value))
    {
      log_error("input string too short");
      return errno = ERROR_STR_TOO_SHORT;
    }

    strncpy(listofanswers[i]->key,
            listofwantedinfo[i],
            maxlengh);
    //sanitizing the content
    listofanswers[i]->key  [strcspn(listofanswers[i]->key  , "\n")] =  '\0';
    listofanswers[i]->value[strcspn(listofanswers[i]->value, "\n")] =  '\0';
  }
  return errno = SUCCESS;
}
/* this funtion is supposed to initialize a new user 
 * it asks for credentials and sets the user up
 * then asks for the prefered configs and writes 
   them to the user config file*/
int initialize_user(const char *list_of_wanted_inf[MAXLEN],
               int number_of_inf,
               int maxlengh,
               size_t bin_hash_len,
               size_t bin_salt_len,
               size_t hex_hash_len,
               size_t hex_salt_len,
               size_t line_maxlen,
               size_t path_maxlen,
               int numbr_of_dirs,
               const EVP_MD *(*hash_function)(void)
               )
{
  char *Locker_folder = malloc(2*MAXLEN*sizeof(char));
  char *config_folder = malloc((2*MAXLEN)*sizeof(char));
  char *accounts_folder = malloc((2*MAXLEN)*sizeof(char));
  char *users_folder  = malloc((2*MAXLEN)*sizeof(char));
  char *password      = malloc(maxlengh*sizeof(char));
  char *username      = malloc(maxlengh*sizeof(char));
  char *config_file   = malloc(maxlengh*sizeof(char));
 //check if malloc failed 
  if (!password || !username || 
    !config_folder || !users_folder)
    return ERROR_MEMORY_ALLOCATION;
  

  /*initiating the configs and users paths*/
  if (SUCCESS != 
    define_paths(Locker_folder,
                 users_folder,
                 config_folder,
                 accounts_folder,
                 MAXLEN,
                 pwd))
    return errno;
  char *dirs[]=
    {Locker_folder,config_folder,users_folder,accounts_folder};
  init_dirs(dirs,numbr_of_dirs,maxlengh);
  if(SUCCESS !=errno )
  {
    return errno;
  }
  //getting the creds
  printf("username> ");
  fgets(username,MAXLEN,stdin);

  printf("password> ");
  fgets(password,MAXLEN,stdin);
  //making the user
if (SUCCESS != 
  make_user(users_folder,
            password,
            username,
            maxlengh,
            bin_hash_len,
            bin_salt_len,
            hex_hash_len,
            hex_salt_len,
            hash_function))
    return errno;   


  /*this will be used to store the configs before writing them*/
  pair **config_couples =malloc(number_of_inf*sizeof(pair*));
  if(!config_couples)
    return errno = ERROR_MEMORY_ALLOCATION;
  /*initializing the structs in the array */
 if(SUCCESS != 
    init_pair_array(config_couples,
                               number_of_inf))
    return errno;
  /*getting the configs from user into the array*/
  if (SUCCESS != getinfo(list_of_wanted_inf,
          number_of_inf,
          maxlengh,
          config_couples))
    return errno;

  /*making the filepath to the user configs
   * the_general_configs_path/username */
  if (SUCCESS != make_file_path(
    config_file,
    config_folder,
    username,
    maxlengh
  ))
    return errno;

  /*writing the configs*/
  if (SUCCESS != write_array_of_pairs(config_file,
                       config_couples,
                       number_of_inf,
                       maxlengh,
                       line_maxlen,
                       path_maxlen))
    return errno;
  /*freeing the structs */
 if(SUCCESS != free_pair_array(config_couples,
                               number_of_inf))
    return errno;
  
  free(username);
  free(password);
  free(config_file);
  free(config_couples);
  free(config_folder);
  free(users_folder);
  free(accounts_folder);
  free(Locker_folder);

  return  errno = SUCCESS;
  
}


/*checks if the necessary directories exist
 * if not it creates them*/

int init_dirs(
  char **dirs_paths,
  int number_of_dirs,
  size_t maxlengh)
{

  /*check for null*/
  if(!dirs_paths){
    log_error("funtion init_dirs");
    return errno = ERROR_NULL_VALUE_GIVEN;
  }
  /*the mode of creation of directories */
  mode_t mode = S_IRWXU;
  for (int i = 0;i < number_of_dirs;i++)
  {
    /*checking the str lenght is in limits*/
    if('\0' != dirs_paths[i][strnlen(dirs_paths[i],maxlengh)]){
      log_error("eror in funtion init_dirs");
      return errno = ERROR_TOO_LONG_STRING;
    }
    /*check if dir exists and store return value in err*/
    directory_exists(dirs_paths[i],maxlengh);
    switch (errno) {
      /*if it exists continue to the next*/
      case SUCCESS:
        continue;
        break;
      case ERROR_DIRECTORY_DOESNT_EXIST:
        /*if it doesnt create it*/
        mkdir(dirs_paths[i],mode);
        continue;
        break;
      default:
        /*report other behaviors*/
        return errno;
        break;
    }
  }
  return errno =SUCCESS;

}
