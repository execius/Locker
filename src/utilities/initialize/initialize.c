// char **initialize(char** listofwantedinfo , int numberofinfos , int maxlengh);
#include "initialize.h"




/*requests the stuff in aarray from the user
 and returns an array chars that is indexed in 
 the same order*/
 
/* it is the responsibility of the caller to free
 * each string in the the listofanswers array
 * using the numberofinfo he gave as an argument*/
int getinfo(const char* listofwantedinfo[] ,
/*the next list is for if you wanna print some stuff
 * before the prompt like options or allerts etc..
 * PLEASE MAKE IT THE SAME SIZE AS THE OTHERS AND PUT 
 * NULL IN THAT INDEX IF NO CLARIFICATION IS NEEDED
 * PUT THINGS IN RESPECTIVE ORDER SO EACH PROMPT AND 
 * IT'S CLARIFICATION HAVE THE SAME INDEX IN THEIR 
 * ARRAYS , IGNORING THIS CAN AND WILL CAUSE MEMORY 
 * CORRUPTION AND ORDERING PROBLEMS*/
            const char* listofclarifications[],
            int numberofinfos , 
            int maxlengh ,
            char **listofanswers)
{

  //error hamdling
  if (!listofanswers || !listofwantedinfo) {
    log_error(
      "error : NULL given, function : getinfo");
    return ERROR_NULL_VALUE_GIVEN;

  }
  //putting the answers in there
  for (int i = 0 ; i < numberofinfos ;i++){
    listofanswers[i] = calloc(maxlengh, sizeof(char));
    
    if(!listofclarifications[i])
      printf("\n %s \n\n > ",listofclarifications[i]);
    printf("\n %s > ",listofwantedinfo[i]);
    fgets(listofanswers[i],maxlengh,stdin);

    if(2 > strlen(listofanswers[i]))
    {
      log_error("input string too short");
      return errno = ERROR_STR_TOO_SHORT;
    }

    //sanitizing the content
    listofanswers[i][strcspn(listofanswers[i]  , "\n")] =  '\0';
    listofanswers[i][strcspn(listofanswers[i]  , "\n")] =  '\0';
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
  char *Locker_folder = calloc(2*maxlengh,sizeof(char));
  char *config_folder = calloc((2*maxlengh),sizeof(char));
  char *accounts_folder = calloc((2*maxlengh),sizeof(char));
  char *users_folder  = calloc((2*maxlengh),sizeof(char));
  char *password      = calloc(maxlengh,sizeof(char));
  char *username      = calloc(maxlengh,sizeof(char));
  char *config_file_path   = calloc(3*maxlengh,sizeof(char));

  char* configs_json_string = NULL ;
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


  /*making a json that has the configs*/
cJSON* json_configs = cJSON_CreateObject();

  if (NULL == json_configs )
    return errno;

  get_data_into_json(json_configs 
                     , list_of_config_parameters
                     ,list_of_configs_clarifications
                     ,NUMBER_OF_CONFIGS
                     ,MAXLEN);
  if(SUCCESS != errno)
    return errno;
  /*making the filepath to the user configs
   * the_general_configs_path/username */
  if (SUCCESS != make_file_path(
    config_file_path,
    config_folder,
    username,
    maxlengh
  ))
    return errno;

  configs_json_string = cJSON_Print(json_configs);
  /*writing the configs*/

   FILE *config_file = fopen(config_file_path,"a");
  if(NULL == config_file )
  {
    return ERROR_FILE_OPENING_FAILED;
  }
  if (0 > fputs(configs_json_string,config_file ))
  {
    fclose(config_file);
    return errno ;
  }

  fclose(config_file);
  free(username);
  free(password);
  free(config_file_path);
  free(config_folder);
  free(users_folder);
  free(accounts_folder);
  free(Locker_folder);
  free(configs_json_string);
  cJSON_Delete(json_configs);

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
