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

int read_lines(unsigned char * dst ,FILE *file, int num_lines, int maxlen) {
    if (NULL == file || NULL == dst) {
        return errno = ERROR_NULL_VALUE_GIVEN;  // Invalid file pointer or line count
  }
  if (num_lines <= 0)
    return num_lines;

  char line[MAXLEN] = "";
  int line_count = 0;

  while (line_count < num_lines) {
    if (  fgets(line, sizeof(line), file) != NULL )
    {
      strncat((char *)dst,line,maxlen) ; // Print or process each line here
      line_count++;
      continue;
    }
    break;
  }


    // Check if we read exactly the requested number of lines
    return line_count == num_lines ? errno=SUCCESS : (errno = ERROR_BAD_ARGUMENT);
}
