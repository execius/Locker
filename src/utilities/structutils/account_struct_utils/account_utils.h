//the eror code is in src/headers/eror_handling/eror_handling.h
//all the globaly defined values are  src/headers/defined_values/defined_values.h

#ifndef ACCOUNT_UTILS_H
#define ACCOUNT_UTILS_H

#include "includes.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include "eror_handling.h"
// #include "utilities.h"
// #include "defined_values.h"
// #include <math.h>
// #include <string.h>
// #include <ctype.h>
//


//account stuff

typedef struct account { 
  char **array;
  int *accountnumber;
} account ;

enum DataType { CHAR_TYPE, INT_TYPE };


/**
 * Initializes the account struct by allocating memory for its components.
 * @param acc Pointer to the account struct to initialize.
 * @return SUCCESS if successful, ERROR_MEMORY_ALLOCATION if memory allocation fails.
 */

int initialize_account(account *acc);


/**
 * Frees the allocated memory in the account struct.
 * @param acc Pointer to the account struct to free.
 * @return SUCCESS if successful, ERROR_MEMORY_ALLOCATION if an error occurs.
 */
int free_account(account *acc);

/* changes a string in acc->array of the account number 
 * @param acc Pointer to account struct to modify
 * @param index the index of the string in the acc->array , in case of changing a string ,
 if you wanna change account number set it to 0
 * @param type , specifies if you want to change a string of the accountnumber 
 - INT_TYPE : change the accountnumber
 -CHAR_TYPE : change a string in acc->array*/
int changemember(struct account* acc,int index ,const char *newval, enum DataType type);

//simply prints a account struct
int printaccount(account accc);

/*duplicates a account struct 
 * @param src pointer to the account struct to duplicate 
 * @param dest initialized account struct that will become a copy of src */
int accountdup(account *src , account *dest);

int account_to_json(account *accc, cJSON *json_obj );

int json_to_account(cJSON *json_obj ,account *accc );

#endif //ACCOUNT_UTILS_H
