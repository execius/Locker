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
void clear_terminal(void) {
#ifdef _WIN32
    system("cls");  // Windows command to clear the screen
#else
    system("clear");  // Unix/Linux/Mac command to clear the screen
#endif
}


void handle_cjson_error(void)
{
      const char* error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL)
    {
      fprintf(stderr, "Error before: %s\n", error_ptr);
    }
    errno = ERROR_CJSON_LIB_FAILURE;

}

