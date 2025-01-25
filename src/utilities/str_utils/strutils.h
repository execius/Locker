#include "includes.h"
#ifndef STR_UTILS
#define STR_UTILS

int free_array(void **arr, int size) ;
void clear_terminal(void) ;
void handle_cjson_error(void);
int read_lines(unsigned char * dst ,FILE *file, int num_lines, int maxlen) ; 
#endif // !STR_UTILS
