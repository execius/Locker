#include "strutils.h"

int free_array(void **arr, int size) {
    if (!arr) 
    return ERROR_MEMORY_ALLOCATION;
    
    for (int i = 0; i < size; i++) {
    if(!arr[i])
        free(arr[i]);
    }
    free(arr);
  return errno =SUCCESS;
}
