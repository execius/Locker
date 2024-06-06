// char **initialize(char** listofwantedinfo , int numberofinfos , int maxlengh);
#include "initialize.h"


//requests the stuff in a array from the user and returns an array that includes the user answer
char **getinfo(char** listofwantedinfo , int numberofinfos , int maxlengh){
  char **listofanswers = malloc((numberofinfos)*sizeof(int));
  if (listofanswers == NULL) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  for (int i = 0 ; i < NUMBEROFINF ;i++){
    printf("\n %s > ",*(listofwantedinfo+i));
    listofanswers[i] = malloc(maxlengh*sizeof(int[69]));
    if (listofanswers[i] == NULL) {
      perror("Failed to allocate memory");
      exit(EXIT_FAILURE);
    }
    fgets(listofanswers[i],maxlengh,stdin);
    size_t len = strlen(listofanswers[i]);
    if (len > 0 && listofanswers[i][len - 1] == '\n') {
      listofanswers[i][len - 1] = '\0';
    }
  }
  return listofanswers;
}
//application of the previous function
char **initialize(){
  char *prompts[NUMBEROFINF] = {
        "usb path (ended with a / )",
        "master password"
    };

    char **answers = getinfo(prompts, NUMBEROFINF, MAXLENGH);
    return answers;
}
