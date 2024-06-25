// char **initialize(char** listofwantedinfo , int numberofinfos , int maxlengh);
#include "initialize.h"




//requests the stuff in a array from the user and returns an array that includes the user answer
int getinfo(char** listofwantedinfo , int numberofinfos , int maxlengh ,char **listofanswers){
  if (listofanswers == NULL) {
    log_error("error : NULL array pointer given, function : getinfo");
    return ERROR_NULL_VALUE_GIVEN;
    
  }
  for (int i = 0 ; i < NUMBER_OF_INIT_VARS ;i++){
    printf("\n %s > ",*(listofwantedinfo+i));
    listofanswers[i] = malloc(maxlengh*sizeof(char));
    if (listofanswers[i] == NULL) {
      log_error("Failed to allocate memory");
      return ERROR_MEMORY_ALLOCATION;
    }
     fgets(listofanswers[i],maxlengh,stdin);
    size_t len = strlen(listofanswers[i]);
    if (len > 0 && listofanswers[i][len - 1] == '\n') {
      listofanswers[i][len - 1] = '\0';
    }
  }
  return SUCCESS;
}
// //application of the previous function
// char **initialize(){
//   char *wanted_info[] = {"username","password","email","platform"};
//     char **answers = getinfo(wanted_info, NUMBER_OF_INIT_VARS , MAXLEN);
//     return answers;
// }
