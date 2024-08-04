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

int pair_isinitialised(pair *couple){
  if(!couple){
    log_error("error: NULL value given , function: pair_isinitialized");
    return ERROR_NULL_VALUE_GIVEN ;

  }
  if(!couple->key || !couple->value ){
    log_error("error: uninitialized pair , function : pair_isinitialized");
    return UNINITIALIZED_ACCOUNT_GIVEN  ;
  }
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

  if(NULL != couple)
    free(couple);
  return SUCCESS;
}

