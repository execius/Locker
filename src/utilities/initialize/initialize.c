// char **initialize(char** listofwantedinfo , int numberofinfos , int maxlengh);
#include "initialize.h"




/*requests the stuff in a array from the user
 and returns an array of couples (key/value)that
 includes the wanted info label and the user answer*/
int getinfo(char** listofwantedinfo ,
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
  for (int i = 0 ; i < NUMBER_OF_INIT_VARS ;i++){
    printf("\n %s > ",*(listofwantedinfo+i));
    fgets(listofanswers[i]->value,maxlengh,stdin);
    strncpy(listofanswers[i]->key,
            listofwantedinfo[i],
            maxlengh);
    //sanitizing the content
    listofanswers[i]->key[strcspn(listofanswers[i]->key, "\n")] =  '\0';
    listofanswers[i]->value[strcspn(listofanswers[i]->value, "\n")] =  '\0';

  }
  return SUCCESS;
}

