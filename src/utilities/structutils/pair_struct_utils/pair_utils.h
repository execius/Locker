//the eror code is in src/headers/eror_handling/eror_handling.h
//all the globaly defined values are  src/headers/defined_values/defined_values.h


#include "includes.h"
#ifndef PAIR_UTILS_H
#define PAIR_UTILS_H

//stuff for a struct for configs that holds a key and value
 typedef struct pair_key_value { 
  char *key;
  char *value;
} pair;
/**
 * Initializes the pair struct by allocating memory for its components.
 * @param couple Pointer to the pair struct to initialize.
 * @return SUCCESS if successful, ERROR_MEMORY_ALLOCATION if memory allocation fails.
 */

int initialize_pair(pair* couple);


/**
 * Frees the allocated memory in the pair struct.
 * @param acc Pointer to the pair struct to free.
 * @return SUCCESS if successful, ERROR_MEMORY_ALLOCATION if an error occurs.
 */

int free_pair(pair* couple);



#endif//PAIR_UTILS_H
