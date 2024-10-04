#include "includes.h"

#ifndef HEX_BIN_UTILS
int binary_to_hex(const unsigned char *bin,
                  size_t len,
                  unsigned char *hex); 

int print_hex(unsigned char* hex,size_t hexlen);
int hex_to_binary(const char *hex,
                  unsigned char *bin, 
                  size_t bin_len);

int compare_creds(const char *credential ,
                         const char *userinput,
                         size_t len);
#endif // !HEX_BIN_UTILS
