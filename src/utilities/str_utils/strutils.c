#include "strutils.h"

int free_array(void **arr, int size) {
    if (!arr) 
    return ERROR_NULL_VALUE_GIVEN;
    
    for (int i = 0; i < size; i++) {
    if(NULL != arr[i])
        free(arr[i]);
    }
    free(arr);
  return errno =SUCCESS;
}
