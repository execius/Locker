#include "strutils.h"

int free_str_array(char **arr, int size) {
    if (!arr) 
    return ERROR_MEMORY_ALLOCATION;
    
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
  return SUCCESS;
}
