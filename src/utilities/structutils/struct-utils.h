#include <stdio.h>
#include <stdlib.h>
#include "eror_handling.h"
#include "utilities.h"
#include "defined_values.h"

#ifndef STRUCT_UTILS_H
#define STRUCT_UTILS_H



typedef struct account { 
  char **array;
  int *accountnumber;
} account ;


 enum DataType { CHAR_TYPE, INT_TYPE };


int initialize_account(account *acc);

int free_account(account *acc);

int changemember(struct account* acc,int index ,const char *newval, enum DataType type);

int printaccount(account accc);

int accountdup(account *src , account *dest);

#endif
