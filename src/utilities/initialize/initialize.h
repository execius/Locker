// char **initialize(char** listofwantedinfo , int numberofinfos , int maxlengh);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defined_values.h"

#ifndef INITIALIZE_H
#define INITIALIZE_H



//requests the stuff in a array from the user and returns an array that includes the user answer
int getinfo(char** listofwantedinfo , int numberofinfos , int maxlengh , char **listofanswers);
char **initialize();

#endif
