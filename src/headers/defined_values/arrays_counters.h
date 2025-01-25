/*read the .c file*/
#include "includes.h"
#ifndef ARRS_CNTS

#define ARRS_CNTS
extern const char *list_of_config_parameters[];
extern const char *account_creds_list[] ; 
extern const char *list_of_configs_clarifications[] ;
extern const char *list_of_accounts_clarifications[] ; 
extern const size_t NUMBER_OF_CONFIGS;
extern const size_t NUMBER_OF_DIRS; 
extern const size_t ACCOUNTS_INFO;

int read_lines(unsigned char * dst ,FILE *file, int num_lines, int maxlen) ;//this is an imposter here 
#endif // DEBUG
