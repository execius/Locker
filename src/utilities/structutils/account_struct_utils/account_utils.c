#include "account_utils.h" 
//initialze : alocate memory and set number to 0
int initialize_account(account *acc){
  if (NULL == acc)
    return ERROR_MEMORY_ALLOCATION;//the account variable could not be allocated
  acc->array = malloc(NUMBEROFINFO*sizeof(char *)) ;
  if(NULL == acc->array) //failed allocation for the array
      return ERROR_MEMORY_ALLOCATION;
  

  for(int i = 0;i<NUMBEROFINFO;i++){
    acc->array[i] = malloc(MAXLEN*sizeof(char)) ;//allocate memory for each object in the array
    if(NULL == acc->array[i]){//couldnt allocate
      for (int j = 0; j < i; j++) {//freeing previous-to-failure alocated memory
        free(acc->array[j]); 
  }
      log_error("error: memory allocation failed, function: initialize_account");
      return ERROR_MEMORY_ALLOCATION;}//checking for allocation erors
  }
  acc->accountnumber = malloc( 1 + (int)log10(MAXNUMBER));
  if(NULL == acc->accountnumber) //failed allocation for the accountnumber
      return ERROR_MEMORY_ALLOCATION;

  *acc->accountnumber = 0; 
  return SUCCESS;
}

// Free allocated memory in account struct
int free_account(account *acc){
  if (NULL == acc || (NULL == acc->array && NULL == acc->accountnumber)) {
    fprintf(stderr, "Info: Nothing to free (acc or acc->array is NULL)\n");
    return SUCCESS;  // Nothing to free
  }
  for (int i = 0; i < NUMBEROFINFO; i++) {
    if (acc->array[i] != NULL) {

      free(acc->array[i]); // freeing members of array
      acc->array[i] = NULL;  // Set to NULL after freeing
    }
  }  free(acc->array); //freeing array
     free(acc->accountnumber);//freeing accountnumber
     acc->accountnumber = NULL;
  return SUCCESS;
}

int isinitialized(account *acc){
  if (NULL == acc) {//checking for NULL value
    log_error("error: NULL value given , function: change_char_member");
        return ERROR_NULL_VALUE_GIVEN ;
  }
  for (int i = NUMBEROFINFO-1 ;i >=0;i--){
    if(NULL == acc->array[i]){//checking if the account array uninitialized
    log_error("error: uninitialized account , function : isinitialized");
    return UNINITIALIZED_ACCOUNT_GIVEN  ;
  }
  }

  if(NULL == acc->accountnumber){//checking if the accountnumber id uninitialized
    log_error("error: uninitialized account , function : isinitialized");
    return UNINITIALIZED_ACCOUNT_GIVEN  ;
  }

  return SUCCESS;
}

int change_char_member(char **account_array_pointer ,int index , const char *newval){
  if (NULL == newval){//check if newval isnt NULL
    log_error("error: NULL value given , function: change_char_member");
        return ERROR_NULL_VALUE_GIVEN ;
  }
  if(index < 0 || index >= NUMBEROFINFO ){//checking if the index in in boundaries
    log_error("error: index out of bounds , function: change_char_member");
        return ERROR_INDEX_OUT_OF_BOUNDS ;
  }
  if(strlen(newval) > MAXLEN ){  //checking lenght is in boundaries 
    log_error("error: string too long  , function: change_char_member");
        return ERROR_TOO_LONG_STRING ;
  }
  strncpy(account_array_pointer[index],newval,MAXLEN);//copy newval into array[INDEX]
    return SUCCESS;
}


int change_int_member(int *account_accountnumber_pointer , const char *newval){
  char *endptr;
  long num = strtol(newval, &endptr, 10);//converting char * to int
  if ('\0' != *endptr){ //checking if the string given was valid 
    log_error("error: newval not a number , function: changemember\n");
    return ERROR_INVALID_INTEGER ;
  }
  if(num > MAXNUMBER){//checking if the index in in boundaries
    log_error("error: newval above maximum, function: changemember\n");
    return ERROR_INVALID_INTEGER ;
  }

  *account_accountnumber_pointer = (int)num;
  return SUCCESS;
}


int changemember( account* acc,int index ,const char *newval,enum DataType type){
  if (index < 0 || index >= NUMBEROFINFO) {//checking if the index in in boundaries
    log_error("error: index out of bounds, function: changemember\n");
    return ERROR_INDEX_OUT_OF_BOUNDS;
  }
  switch (type){ ////checking the type indicator
    case INT_TYPE:
      return change_int_member(acc->accountnumber,newval);
    case CHAR_TYPE :
      return change_char_member(acc->array,index,newval);
    default:
      log_error("error: bad type indicator given, function: changemember\n");
      return ERROR_UNKNOWN_TYPE;
  }
  return SUCCESS;

}

int accountdup(account *src ,account *dest){
  
  if(NULL == src || NULL == dest){//checking for NULL values
    log_error("error: NULL account pointer given , function : accountdup");
    return ERROR_NULL_VALUE_GIVEN  ;
  } 
  if (SUCCESS != isinitialized(src) || SUCCESS != isinitialized(dest)){//checking id the accounts are initialized
    log_error("error: uninitialized account , function : accountdup");
    return UNINITIALIZED_ACCOUNT_GIVEN  ;

  } 

  
  for(int i = 0;i<NUMBEROFINFO;i++){//copying strings from src to dest
    strncpy(dest->array[i],src->array[i],MAXLEN);
  }
  
  *dest->accountnumber = *src->accountnumber;//copying int from src to dest
  
  
  return SUCCESS;
}

int printaccount(account accc){

  if(SUCCESS != isinitialized(&accc)){//checking if the account given id uninitialized
    log_error("error: uninitialized account , function : printaccount");
    return UNINITIALIZED_ACCOUNT_GIVEN  ;
  }
  
  printf("%s\n %s\n %s\n %s\n %d\n",
         accc.array[USERINDEX],
         accc.array[EMAILINDEX],
         accc.array[PASSWORDINDEX],
         accc.array[PLATFORMINDEX],
         *accc.accountnumber);
  return SUCCESS;
}


