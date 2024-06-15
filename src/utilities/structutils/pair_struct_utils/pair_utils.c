#include "pair_utils.h"


int initialize_pair(pair* couple){
  if (NULL == couple)
    return ERROR_MEMORY_ALLOCATION;//the pair variable could not be allocated
  
  couple->key = malloc(MAXLEN*sizeof(char *)) ;
  if(NULL == couple->key) //failed allocation 
    return ERROR_MEMORY_ALLOCATION;
  
  couple->value = malloc(MAXLEN*sizeof(char *)) ;
  if(NULL == couple->value) //failed allocation 
    return ERROR_MEMORY_ALLOCATION;

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

