#include "includes.h"
#ifndef DEFINED_VALS

#define DEFINED_VALS

#define pwd getenv("PWD")
#define home getenv("HOME")

#define VERSION 1.0
enum constant_values{
  NUMBEROFINFO = 4, //number of infos in the accounts struct
  USERINDEX = 0,
  EMAILINDEX = 1,
  PASSWORDINDEX = 2,       //indexes of different information in the array inside account struct
  PLATFORMINDEX = 3,
  NUMBER_OF_CONFIG_INFORMATION = 4, 
  MAXLEN = 4096,      //maximum string lengh
  PATH_SIZE = 2*MAXLEN,
  MAXNUMBER = 9999,   //maximum int value
  NUMBER_OF_INIT_VARS = 4, //number of thing that we will ask the user for in the initialization
  SHA256_SALT_SIZE = 16,
  SHA256_HASH_SIZE_BYTES = 32,
  KEY_SIZE_256 = 32,
  AES_256_BLOCK_SIZE = 16,
  MAX_CIPHER_SIZE = MAXLEN+(16-(MAXLEN%16)),
  SHA256_SALT_SIZE_HEX = 2*SHA256_SALT_SIZE+1,
  SHA256_HASH_SIZE_HEX = 2*SHA256_HASH_SIZE_BYTES+1
};

int define_paths(
    char *Locker_folder,
    char *users_folder,
    char *configs_folder,
    size_t maxlen,
    char *PWD);
#endif // !DEFINED_VALS


