#include "struct-utils.h" 
#include <string.h>
#include <ctype.h>

int change_char_member(account *acc ,int index , const char *newval){
  if(index <= NUMBEROFINFO && strlen(newval) <= MAXLEN && *newval){
    (acc->array)[index] = strdup(newval);
    return SUCCESS;

  }
  else {
     log_error("error: memory allocation failed, function: changemember");
        return ERROR_MEMORY_ALLOCATION ;
    }  


}


int change_int_member(account *acc , const char *newval){
  char *endptr;
  long num = strtol(newval, &endptr, 10);
  if (*endptr == '\0' && num <= MAXNUMBER){ 
    acc->accountnumber = (int)num;
    return SUCCESS;}
  else {
    log_error("error: newval not int or above maximum, function: changemember\n");
    return ERROR_INVALID_INTEGER ;    }
}


int changemember( account* acc,int index ,const char *newval,enum DataType type){
  if (index < 0 || index >= NUMBEROFINFO) {
    log_error("error: index out of bounds, function: changemember\n");
    return ERROR_INDEX_OUT_OF_BOUNDS;
  }
  switch (type){
    case INT_TYPE:
      return change_int_member(acc,newval);
    case CHAR_TYPE :
      return change_char_member(acc,index,newval);
    default:
      log_error("error: bad type indicator given, function: changemember\n");
      return ERROR_UNKNOWN_TYPE;
  }
  return SUCCESS;

}
