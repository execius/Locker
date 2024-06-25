//the eror code is in src/headers/eror_handling/eror_handling.h
//all the globaly defined values are  src/headers/defined_values/defined_values.h


#include "includes.h"

#ifndef INITIALIZE_H
#define INITIALIZE_H



//requests the stuff in a array from the user and returns an array that includes the user answer
int getinfo(char** listofwantedinfo , int numberofinfos , int maxlengh , char **listofanswers);
char **initialize(void);

#endif
