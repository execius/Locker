/*this file is fo globaly defined arrays and the
 counts of their elements*/
#include "arrays_counters.h"

/*make sure to increase the number of initialization info 
 if the .h file whenever you add a new element to this list*/
const char *list_of_config_parameters[] = 
  {"encryption","hashing"};


const char *account_creds_list[] = 
  {"user","email", "password" };


const char *list_of_configs_clarifications[] = 
  {"lulz","blah blah"};

const char *list_of_accounts_clarifications[] = 
  {NULL,NULL,NULL};
int read_lines(unsigned char * dst ,FILE *file, int num_lines, int maxlen) {
    if (NULL == file || NULL == dst) {
        return errno = ERROR_NULL_VALUE_GIVEN;  // Invalid file pointer or line count
  }
  if (num_lines <= 0)
    return num_lines;

  char line[maxlen];
  int line_count = 0;

  while (line_count < num_lines && fgets(line, sizeof(line), file) != NULL) {
    strncat((char *)dst,line,maxlen) ; // Print or process each line here
    line_count++;
    }


    // Check if we read exactly the requested number of lines
    return line_count == num_lines ? errno=SUCCESS : (errno = ERROR_BAD_ARGUMENT);
}
