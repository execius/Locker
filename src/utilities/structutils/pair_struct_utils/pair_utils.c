#include "pair_utils.h"


int initialize_pair(pair* couple){
  if (NULL == couple){
    log_error("NULL pair pointer given, function : initialize_pair");
    return errno = ERROR_NULL_VALUE_GIVEN;//the pair variable could not be allocated
  }
  couple->key = malloc(MAXLEN*sizeof(char *)) ;
  if(NULL == couple->key){ //failed allocation 
    log_error("could not allocate memory for key,  function : initialize_pair");
    return errno = ERROR_MEMORY_ALLOCATION;}

  couple->value = malloc(MAXLEN*sizeof(char *)) ;
  if(NULL == couple->value){ //failed allocation 
    log_error("could not allocate memory for value ,  function : initialize_pair");
    return errno =  ERROR_MEMORY_ALLOCATION;}

  return errno = SUCCESS;
}
/*allocates and initializes pairs in a pair array*/
int init_pair_array(pair **pairs,
                    int number_of_pairs)
{
  //check for null
  if (!pairs){
    log_error("init_pair_array:null value");
    return errno = ERROR_NULL_VALUE_GIVEN;
  }

  //allocating and initializing
  for (int i = 0 ; i < number_of_pairs ;i++){
    pairs[i] = malloc(sizeof(pair));
    if(!pairs[i]){
      log_error("init_pair_array:null value");
      return errno =  ERROR_NULL_VALUE_GIVEN;
    }
    if (SUCCESS != initialize_pair(pairs[i]))
      return errno;
  }
  return errno = SUCCESS;
}

int pair_isinitialised(pair *couple){
    //check for null
  if(!couple){
    log_error("error: NULL value given , function: pair_isinitialized");
    return errno = ERROR_NULL_VALUE_GIVEN ;

  }
  if(!couple->key || !couple->value ){
    log_error("error: uninitialized pair ");
    return errno =  UNINITIALIZED_STRUCT_GIVEN  ;
  }
  return errno = SUCCESS;
}


int free_pair(pair* couple){
  if (NULL == couple || (NULL == couple->key && NULL == couple->value)) {
    return errno = SUCCESS;  // Nothing to free
  }
  if(NULL != couple->key)
    free(couple->key);

  if(NULL != couple->value)
    free(couple->value);

  return errno = SUCCESS;
}
/*frees each pair and its members in a array*/
int free_pair_array(pair **pairs,
                    int number_of_pairs)
{
  //check for null
  if (!pairs){
    printf("what the fuck\n");
    log_error("free_pair_array:null value");
    return ERROR_NULL_VALUE_GIVEN;
  }

  //allocating and initializing
  for (int i = 0 ; i < number_of_pairs ;i++){
    if (NULL == pairs[i] ){
      continue;
    }
    if (SUCCESS != free_pair(pairs[i]))
      return errno;
    free(pairs[i]);
  }
  return errno = SUCCESS;
}

