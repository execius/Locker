// char **initialize(char** listofwantedinfo , int numberofinfos , int maxlengh);
#include <stdio.h>
#include <stdlib.h>

#define NUMBEROFINF 2 //number of thing that we will ask the user for
#define MAXLENGH 1000 //maximum lengh of the user input

//requests the stuff in a array from the user and returns an array that includes the user answer
char **getinfo(char** listofwantedinfo , int numberofinfos , int maxlengh){
  char **listofanswers = malloc((numberofinfos)*sizeof(int));
  for (int i = 0 ; *(listofwantedinfo+i) != NULL ;i++){
    printf("\n %s > ",*(listofwantedinfo+i));
    listofanswers[i] = malloc(maxlengh*sizeof(int[69]));
    fgets(listofanswers[i],maxlengh,stdin);
  }
  return listofanswers;
}
//application of the previous function
char **initialize(){
  char **test = malloc(NUMBEROFINF*sizeof(int));
  test[0] = "usb path (ended with a / )";
  test[1] = "master password";
  char **tst = malloc(NUMBEROFINF*sizeof(int));
  tst = getinfo(test,NUMBEROFINF,MAXLENGH);
  return tst;
}

