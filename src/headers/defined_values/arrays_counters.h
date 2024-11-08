/*read the .c file*/
#include "includes.h"
#ifndef ARRS_CNTS

#define ARRS_CNTS
extern const char *list_of_wanted_inf[];
extern const char *account_creds_list[] ; 

enum counters
{ 
  NUMBER_OF_CONFIGS =4,
  NUMBER_OF_DIRS =4,
  ACCOUNTS_INFO = 4
};
int read_lines(unsigned char * dst ,FILE *file, int num_lines, int maxlen) ;//this is an imposter here 
#endif // DEBUG
