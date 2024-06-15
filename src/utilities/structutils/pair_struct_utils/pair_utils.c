#include "pair_utils.h"


int initialize_pair(pair* couple){
  if (NULL == couple){
    log_error("NULL pair pointer given, function : initialize_pair");
    return ERROR_NULL_VALUE_GIVEN;//the pair variable could not be allocated
  }
  couple->key = malloc(MAXLEN*sizeof(char *)) ;
  if(NULL == couple->key){ //failed allocation 
    log_error("could not allocate memory for key,  function : initialize_pair");
    return ERROR_MEMORY_ALLOCATION;}

  couple->value = malloc(MAXLEN*sizeof(char *)) ;
  if(NULL == couple->value){ //failed allocation 
    log_error("could not allocate memory for value ,  function : initialize_pair");
    return ERROR_MEMORY_ALLOCATION;}

  return SUCCESS;
}



int free_pair(pair* couple){
  if (NULL == couple || (NULL == couple->key && NULL == couple->value)) {
    return SUCCESS;  // Nothing to free
  }
  if(NULL != couple->key)
    free(couple->key);

  if(NULL != couple->value)
    free(couple->value);

  return SUCCESS;
}

