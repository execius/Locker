#include <stdio.h>
#include <stdlib.h>
#include "eror_handling.h"

#ifndef STRUCT_UTILS_H
#define STRUCT_UTILS_H

#define NUMBEROFINFO 4

#define USERINDEX 0
#define EMAILINDEX 1
#define PASSWORDINDEX 2 
#define PLATFORMINDEX 3

#define MAXLEN 4096
#define MAXNUMBER 9999


typedef struct account { 
  char **array;
  int accountnumber;
} account ;


 enum DataType { CHAR_TYPE, INT_TYPE };


int initialize_account(account *acc);

int free_account(account *acc);


int changemember(struct account* acc,int index ,const char *newval, enum DataType type);

#endif
