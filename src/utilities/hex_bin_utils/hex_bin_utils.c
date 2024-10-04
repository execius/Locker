#include "hex_bin_utils.h"
int binary_to_hex(const unsigned char *bin,
                  size_t len,
                  unsigned char *hex) {

    for (size_t i = 0; i < len; i++) {
        sprintf((char *)(hex + (i * 2)), "%02x", bin[i]);
    }
    hex[len * 2] = '\0';
  return SUCCESS;
}


int hex_to_binary(const char *hex,
                  unsigned char *bin, 
                  size_t bin_len) {

    for (size_t i = 0; i < bin_len; i++) {
        sscanf(hex + (i * 2), "%02x",(unsigned int *) &bin[i]);
    }
  return SUCCESS;
}

/*compares two binary credentials */
int compare_creds(const char *credential ,
                         const char *userinput,
                         size_t len){

  if (0 != CRYPTO_memcmp(credential,userinput,len))
    return (errno = ERROR_INVALID_CREDENTIALS);
  return  errno =SUCCESS;
 }

